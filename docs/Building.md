# Building and development

Building Missile Toad requires a set of tools that need to be installed on your system.

The following sections will guide you through the process of installing these tools.

## Prerequisites

* [CMake](https://cmake.org/download/) 3.25 or higher
* [Git](https://git-scm.com/downloads)
* A C++ compiler with C++20 support, tested only with the newest versions of:
  * [GCC](https://gcc.gnu.org/)
  * [Clang](https://clang.llvm.org/)
  * [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/)
  * [Apple Clang](https://developer.apple.com/documentation/xcode-release-notes/xcode-12-release-notes)

Additionally, you will need the following tools to work with the project:
* [Python](https://www.python.org/downloads/): used for scripts and pre-commit hooks
* [Doxygen](https://www.doxygen.nl/download.html): used to generate documentation
* [PlantUML](https://plantuml.com/download): used to generate UML diagrams
* [Clang Tidy](https://clang.llvm.org/extra/clang-tidy/): used to check code style
* [Clang Format](https://clang.llvm.org/docs/ClangFormat.html): used to format code

Optionally, you can install the following tools to improve your development experience:
* [Ninja](https://ninja-build.org/): used to build the project
* [Ccache](https://ccache.dev/): used to cache compilation results
* [Just](https://github.com/casey/just): used to run some scripts (see justfile)

## Building

The process of building Missile Toad is very simple. In fact, we only rely on CMake to do all the work for us.
The process is similar for all platforms, but we will focus on Linux here.

1. Clone the repository
    ```bash
    git clone
    ```
2. Create a build directory
    ```bash
    mkdir build && cd build
    ```
3. Configure the project. Note that we specify CMAKE_EXPORT_COMPILE_COMMANDS to generate a compilation database for clang-tidy.
    ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Debug -DGRAPHICS=GRAPHICS_API_OPENGL_ES2 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    ```
4. Build the project
    ```bash
      cmake --build . -j <number of threads>
    ```
5. Run the tests
    ```bash
    ctest -j <number of threads>
    ```

## Committing
Before committing, you could run pre-commit hooks to check for errors and format the code. To do so, you need to install the pre-commit package:
```bash
pip install pre-commit
```
Then, you can install the hooks:
```bash
pre-commit install
```
Now, every time you commit, the hooks will run and check for errors and formatting issues. If there are any, the commit will be aborted, and you will have to fix the issues before committing again.

## Documentation
To generate the documentation, you need to install Doxygen and PlantUML. Then, you can run the following command:
```bash
doxygen Doxyfile
```
The documentation will be generated in the `docs` folder.

## Static analysis
To run static analysis, you need to install Clang Tidy. Then, you can run the following command:
```bash
cmake --build . --target tidy
```

## Formatting
To format the code, you need to install Clang Format. Then, you can run the following command:
```bash
cmake --build . --target format
```

## Using Just
If you have installed the Just tool, you can use the justfile to run some scripts. For example, you can run the tests with:
```bash
just test
```
Or you can run the static analysis with:
```bash
just lint
```

Check the justfile for more commands.
