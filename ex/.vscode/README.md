# Basic testing VScode config

## Setup

- ensure that the `.vscode` folder is located in the root of the project opened in VScode; this can either be the folder of the single exercise, or a folder containing all other exercise's folders.

## Files

Contains 2 json files:
- `tasks.json`: build and run tasks, to run either all tests, or a single one (C test file opened in the editor).
  - Ctrl + Shift + B, to run default build
  - Ctrl + P to open command panel, type "task " to show all tasks
- `launch.json`: debug binary tests or implementation, and I/O tests (name of input file selectable from the dropdown). 
  - Ctrl + Shift + D to open Debug panel
