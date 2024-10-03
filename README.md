# Calculator

## Brief
**This is a calculator built on the idea of [Reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)**
### Demo
Example of calculating 2 power 3:

<img src="demo/Calculator.gif" alt="Calculator Operation" width="200"/>



### Technical
- Language: C++17 standard
- External libraries: Qt, Catch2, fmt
- Programming technique: OOAD, Architecture design, Design patterns, Plugin development
- External libraries installed and managed by
  - [CPM](https://github.com/cpm-cmake/CPM.cmake) Package Manager
- Unit testing using [Catch2](https://github.com/catchorg/Catch2) v2
- Code documentation with [Doxygen](https://doxygen.nl/)
- Tooling: Clang-Format, Cmake-Format, Clang-tidy, Sanitizers

## Structure

``` text
├── CMakeLists.txt
├── app
│   ├── CMakesLists.txt
│   └── main.cc
├── cmake
│   └── cmake modules
├── docs
│   ├── Doxyfile
│   └── html/
├── external
│   ├── CMakesLists.txt
│   ├── ...
├── src
│   ├── CMakesLists.txt
│   ├── foo/...
│   └── bar/...
└── tests
    ├── CMakeLists.txt
    └── test_*.cc
```

Library code goes into [src/](src/), main program code in [app/](app) and tests go in [tests/](tests/).

## Software Requirements

- CMake 3.21+
- GNU Makefile
- MSVC 2017 (or higher), G++9 (or higher), Clang++9 (or higher)
- Qt 6.7.2

## Building

First, clone this repo and do the preliminary work:



- App Executable
*Edit Qt path in CmakeList.txt*

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
cd app
./main
```

- Unit testing

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE="Debug"
cmake --build build --config Debug
cd build
ctest .
```

For more info about CMake see [here](./README_cmake.md).
