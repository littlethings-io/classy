# Classy C++ Starter Project

This repository is a small C++ project intended for learning and teaching.
It includes the compiler, CMake, Make, and GoogleTest, so you do not need to
install a separate C++ toolchain.

## Requirements

You only need to install **Python 3.9 or newer** and make sure the `python`
command is available in your terminal.

Everything else required to configure, compile, and test the project is
included in this repository.

> This setup currently supports **Windows only**. Linux support might be added
> later.

## Building and running

Open Command Prompt or PowerShell in the repository folder and run:

```powershell
python run.py
```

The script displays this menu:

```text
0. Clean build
1. Build
2. Build and run
3. Run
4. Delete build folder
5. Run all Google tests
6. Run test target
```

The commands do the following:

- **Clean build** deletes `build/build-app` and rebuilds the application without
  touching the unit-test build.
- **Build** configures CMake and performs an incremental build.
- **Build and run** builds the project and then starts `classy.exe`.
- **Run** starts the previously built `classy.exe` without rebuilding it.
- **Delete build folder** removes both generated build trees.
- **Run all Google tests** uses the separate test tree to build only the unit
  tests, then runs every discovered GoogleTest through CTest.
- **Run test target** builds only the unit tests in the separate test tree,
  then runs CMake's `test` target.

The generated program is placed at:

```text
build/build-app/classy.exe
```

Application and test builds use separate folders so switching between them is
fast and does not reconfigure or overwrite the other build:

```text
build/
├── build-app/
└── build-tests/
```

## Project entry point

`main/src/main.cpp` stays small and only calls:

```cpp
modules_main::Run();
```

The main program logic belongs in:

```text
modules/modules_main/src/modules_main.cpp
```

`modules_main` can include and call code from the other modules.

## Adding a module

Create a new folder directly inside `modules`. Use a simple target name made
from letters, numbers, and underscores. For a module named `calculator`, create:

```text
modules/
└── calculator/
    ├── CMakeLists.txt
    ├── inc/
    │   └── calculator.hpp
    └── src/
        └── calculator.cpp
```

Add this to `modules/calculator/CMakeLists.txt`:

```cmake
add_classy_module(calculator)
```

Example header, `modules/calculator/inc/calculator.hpp`:

```cpp
#pragma once

namespace calculator
{
int Add(int left, int right);
}
```

Example source, `modules/calculator/src/calculator.cpp`:

```cpp
#include "calculator.hpp"

namespace calculator
{
int Add(int left, int right)
{
    return left + right;
}
}
```

You do not need to edit the root `CMakeLists.txt`. The module is detected,
built as a library, and made available to `modules_main` automatically.

For example, it can be used from `modules_main.cpp` like this:

```cpp
#include "calculator.hpp"

int result = calculator::Add(2, 3);
```

Run **Build** or **Build and run** after adding the module.

## Adding module tests

Tests are optional. Add a `test` or `tests` folder inside the module:

```text
modules/
└── calculator/
    ├── CMakeLists.txt
    ├── inc/
    ├── src/
    └── test/
        └── calculator_test.cpp
```

Example test:

```cpp
#include "calculator.hpp"

#include <gtest/gtest.h>

TEST(CalculatorTest, AddsTwoNumbers)
{
    EXPECT_EQ(calculator::Add(2, 3), 5);
}
```

When unit tests are enabled, every C++ source file under a module's `test` or
`tests` folder is added automatically. You do not need to list test files in
the module's `CMakeLists.txt`.

Use **Run all Google tests** or **Run test target** from `run.py` to build and
run the tests.

## Editor support

The project includes `.clangd` and `.clang-format` configuration files. CMake
generates `build/build-app/compile_commands.json` during an application build,
allowing clangd-aware editors to find the project headers and understand the
build configuration.
