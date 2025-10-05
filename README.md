# C Calculator

A simple interactive command-line calculator that supports basic arithmetic operations (+, -, *, /), parentheses, and variable assignments.

## Features

*   Basic arithmetic operations: `+`, `-`, `*`, `/`
*   Support for parentheses `()`
*   Variable assignment: `x = 10`
*   Uses variables in expressions
*   `exit` command to quit the calculator

## Project Structure

The project is organized into the following directories:

- `include/`: Contains all the header files (`.h`).
- `src/`: Contains all the source code files (`.c`).
- `Makefile`: The build script for the project.

## How to Build and Run

To compile the project, simply run the `make` command:

```sh
make
```

This will create an executable file named `calculator` in the `build` directory.

To run the calculator, execute the following command:

```sh
./build/calculator
```

To clean up the build files, you can run:

```sh
make clean
```