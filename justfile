default: configure-debug build-debug

configure-debug:
    mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DGRAPHICS=GRAPHICS_API_OPENGL_43

configure-release:
    mkdir -p build-release && cd build-release && cmake .. -DCMAKE_BUILD_TYPE=Release -DGRAPHICS=GRAPHICS_API_OPENGL_43

build-debug:
    cd build && cmake --build . --config Debug -j 8

build-release:
    cd build-release && cmake --build . --config Release -j 8

lint:
    find missile_toad/ -iname *.cpp -o -iname *.hpp | xargs clang-format -i
    find tests/ -iname *.cpp -o -iname *.hpp | xargs clang-format -i

test:
    cd build && ctest --output-on-failure

clean:
    rm -rf build build-release

gen-system:
    python3 scripts/missiletoad.py system $(name)