# TODO

## Build

```bash
mkdir build && cd build
cmake .. -DGRAPHICS_API_OPENGL_43=ON -DCMAKE_BUILD_TYPE=Release -DGRAPHICS=4.3
cmake --build . --config Release
```

> Note: GRAPHICS can be set to ES 2.0 to support OpenGL ES 2.0 (Android, Raspberry Pi, etc.)