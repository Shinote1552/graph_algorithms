
# Graph Algorithms Project Specification

## Project Overview
This project implements comprehensive graph algorithms and data structures including:
- Graph representation (adjacency matrix)
- Traversal algorithms (BFS, DFS)
- Pathfinding (Dijkstra, Floyd-Warshall)
- Minimum Spanning Tree (Prim's algorithm)
- Traveling Salesman Problem (Ant Colony Optimization)
- Supporting data structures (Stack, Queue)

- Part 6. Bonus is not realized

## Authors
- **edmurepi | TTGLShinote**
- **foetidpo**

## License
School21 License (see LICENSE file)

## System Requirements

### Supported Platforms
- Windows (MSYS2/MinGW)
- Linux (GCC)
- macOS (GCC)

### Dependencies
- C11/C++17 compatible compiler
- CMake 3.12+ (for CMake builds)
- Makefile is aviable to
- Google Test (gtest/gmock)
- Clang-format (for code formatting)

### Style Guide
- Google C++ Style
- C11/C++17 standards

## Building project

#### Basic asists for Makefile
- `make all` Full build and test
- `make test`	Build and run tests
- `make cli`	Build CLI executable
- `make cli_static`	Build static CLI (Windows/Linux only)
- `make clean`	Remove build artifacts
- `make reb`	Clean and rebuild
- `make format`	Format code
- `make check_style` Verify code style

#### Basic asists for Makefile
```bash
mkdir build && cd build
cmake ..
cmake --build .
```
#### Targets
- `build_all`	Build all components
- `main_test`	Test executable
- `GAC`	CLI program
- `GAC_static`	Static CLI (Windows/Linux)
- `run_tests`	Execute tests
- `run_cli`	Run CLI
- `format_code`	Format source code

### Output Artifacts
Binaries
- `code-samples/test_bin/` - Test executables
- `code-samples/cli_bin/` - CLI programs
Data Files:
- `data-samples/` - Example graphs


### Platform-Specific Notes
Windows

- Requires MSYS2 environment
- Static builds link against ucrt64
- Default paths for `E:/MSYS2` installation
- needs gtest for tests

macOS

- Dynamic linking only
- Requires Homebrew for dependencies
- Includes Cocoa framework
- needs gtest for tests


Linux

- Full static linking support
- Uses system gtest installation
- needs gtest for tests
