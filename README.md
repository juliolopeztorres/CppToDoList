# To-Do list

Simple C++ CLI application to handle a list of `Tasks` stored in a specified path containing a JSON. 
A default `store.json` would be created in the execution path if none is entered. The more general use case is:

```

PATH\TO\APP> app.exe .\my_store.json

```

Any feedback would be welcome.

## Dependencies

Dependencies are managed through `vcpkg` and compilation with `CMake`. The necessary packages are:

- [nlohmann-json](https://github.com/nlohmann/json)		| 3.10.5 | Handle and mapping JSON data
- [gtest](https://github.com/google/googletest)			| 1.11.0 | Run `unit test` suite

## Build

Visual Studio 2022 Community Edition was used to develop the programm, along with [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage) and its [plugin](https://github.com/OpenCppCoverage/OpenCppCoveragePlugin)  to get Code Coverage feedback.

## Code Structure

Code is structured in different layers called `Framework`, `Domain` and `Data`. Each one with its own dependency hierarchy. This is just one approach to denominated `Clean Architecture` to get code easy to read, structured and testable. See [Clean Architecture](https://8thlight.com/blog/uncle-bob/2012/08/13/the-clean-architecture.html).

![image](https://user-images.githubusercontent.com/11597234/33989292-3f18e720-e0c7-11e7-959f-1ce5b1e4a63c.png)