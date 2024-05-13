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

