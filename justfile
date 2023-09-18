# Default is to build the project
default: build

alias fmt := format
alias b := build
alias c := configure
alias t := test
alias g := gen

# Configure the project. Requires build type (Debug, Release, MinSizeRel, RelWithDebInfo)
configure type:
    mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE={{type}} -DGRAPHICS=GRAPHICS_API_OPENGL_ES2

# Build the project, requires configure
build:
    cd build && cmake --build . -j 8

# Format the project, requires configure
format:
    cd build && cmake --build . --target format

# Run clang-tidy on the project, requires configure
tidy: format
    cd build && cmake --build . --target tidy -j 8

# Run the project, requires configure
test:
    cd build && ctest --output-on-failure

# Clean the project
clean:
    rm -rf build

# Generate a new project file (component, system) in the project
gen type name:
    python scripts/missiletoadcli.py {{type}} {{name}}

docs:
    doxygen docs/Doxyfile
    sphinx-build -b html docs build/docs/sphinx
