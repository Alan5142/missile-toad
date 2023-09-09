# Default is to build the project
default: build

# Configure the project. Requires build type (Debug, Release, MinSizeRel, RelWithDebInfo)
configure type:
    mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE={{type}} -DGRAPHICS=GRAPHICS_API_OPENGL_ES2

# Build the project, requires configure
build:
    cd build && cmake --build . -j 8

# Format the project, requires configure
format:
    cd build && cmake --build . --target format

# Lint the project, requires configure
lint: format
    cd build && cmake --build . --target lint

# Run the project, requires configure
test:
    cd build && ctest --output-on-failure

# Clean the project
clean:
    rm -rf build

# Generate a new system, requires name
gen-system name:
    python scripts/missiletoad.py --name {{name}}
