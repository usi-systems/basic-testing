# Basic testing Jetbrains CLion config

## Setup

- Import the external tools from the `CLion-bt-tools.zip` into your IDE, from `File > Manage IDE settings > import settings...`;
> These tools are used to interface the IDE with the make scripts, and are necessary to use the run/debug configurations from CLion.
> They are stored globally, but you can easely delete them once they're not necesary anymore.

## Files

Contains:
- 2 configurations
  - `Run`: to run a single test file (file in the `tests/` folder) selected in the editor, or all the tests when an implementation file is selected (or any file in the same folder as the `Makefile`)
  - `Debug Single test`: when run in `Debug` mode, allows to use the integrated debugger of CLion to debug a test (opened and selected in the editor) 
  - `Debug IO`: when run in `Debug` mode, allows to debug the IO tests (with `test.in` and `test.out` files)
