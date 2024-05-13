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

