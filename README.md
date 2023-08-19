# TODO

DESC TODO

## Status
![Build and test](https://github.com/Alan5142/missile-toad/actions/workflows/build_test.yml/badge.svg)
![Clang Tidy](https://github.com/Alan5142/missile-toad/actions/workflows/clang_tidy.yml/badge.svg)
![Clang Format](https://github.com/Alan5142/missile-toad/actions/workflows/format.yml/badge.svg)

## Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DGRAPHICS=GRAPHICS_API_OPENGL_43
cmake --build . -j 0
```

**Note: GRAPHICS can be set to ES 2.0 to support OpenGL ES 2.0 (Android, Raspberry Pi, etc.)**
