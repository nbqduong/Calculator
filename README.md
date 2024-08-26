# Template


**Template project information**.
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
- Doxygen
- MSVC 2017 (or higher), G++9 (or higher), Clang++9 (or higher)
- Optional: Code Coverage (only on GNU|Clang): gcovr
- Optional: Makefile, Doxygen

## Building

First, clone this repo and do the preliminary work:



- App Executable

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

- Documentation

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target docs
```

- Code Coverage (Unix only)

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=On
cmake --build build --config Debug --target coverage -j4
cd build
ctest .
```

For more info about CMake see [here](./README_cmake.md).
