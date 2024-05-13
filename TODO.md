# Todo (nick)

- [x] Look if possible to invoke task from launch.json, and shows in button.
- > conclusion: Not possible to add button, or custom "Run" task: possible to just run it 
- [x] Determine if file is implementation or test (in tests directory)
- [x] CLion debugging

## 19.04

- [/] investigate files appearing when running run configurations
- [/] analyze problem of shell scripts (when/where interpreter is chosen)
- [/] look workings with shell/IO tests

- If time, generate automatically tests
  - ~ CLI to generate folder and file structure
  - lookup Unity C

-> Ideas: m4 to fill up boilerplate
  ```m4
  include(bt.m4)      // implicit

  Suite(name)         // sets current suite/file to generate
  Test_compile()
  Test_alloc_ok(type) // type is the type declaration
  
  ```
-> Nope

## 26.04

- [ ] look workings with shell/IO tests
  - Run can just run everything
  - Debug has to make choiches, so better to have a debug target handling it?:
    - make debug file.ext
    - > if ext == c; then compile, cp to debugme, and run it (ez, done);
      > if ext == in | expected; then needs some input redirection (hard);
      > if ext == sh; then needs to run the program as in the shell script?? (Hardest);
- [x] investigate files appearing when running run configurations
  - ? touch only with `if [[ -f ... ]]; then touch ... fi;`?
  - touch $fileName$ can create file in projectDir directory;
  -> TODO: should all be from same dir as makefile, instead of projectDir?
- [ ] analyze problem of shell scripts (when/where interpreter is chosen)
- [x] VScode not showning tasks anymore (ex/example11)
  -> .vscode or .idea folder must be in root of the project 

## 10.05

- Will there ever be test sets with more than one of IO / sh / c-cxx? 
  - (y/n): (__**Kinda, shell could also be IO, but all confined in .sh file**__)
  - Specific run configuration file for each type of set?
  - makefile to make all decisions, based on `TESTS_(IO|SH|C|CXX)` variables?

- Types
  - Shell: Used to test/run binary implementation with specific arguments (e.g cli), (!?!)or other uses?
  - I/O: Used to test/run binary implementation, with specific stdin, and expected output
  - c/cpp src files: Used to test library implementations

- Debugging problems:
  - Library: None, just copy the test
  - Binary programs: 
    - how to select the correct compiled binary, to copy into a file named `debugme`?
      - Need to open src file anyway?
      - Makefile script to choose when project is library, or test suite, so which compiled binary to copy. 
    - usually I/O or shell, so see below problems
  - Shell: 
    - how to get the arguments present in the shell script, to pass to the binary?
  - I/O: choose which .in file to run
    - Manual prompt?


- Proposal:
  - Common `Run all` configuration
    - CLion: Run configuration (Button)
    - VScode: Run task, instructions needed for keyboard shortcut
      - <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>B</kbd>
  - Specific debug configuration, for each test suite type (either)
    - Library: currently open `test.c` or `test.cc` file
    - IO: prompt to pickup file for stdin redirect
      - Clion: either file, or name prompt
      - VScode: can be configurable/generetable, by adding a specific field at the end of the file

### TODO

- [ ] Stabilize current solution
  - [ ] Check which files are necessary to make everything work
- [ ] explore debugging for sh files
- [ ] ocmplete section 1 of report, start section 2
