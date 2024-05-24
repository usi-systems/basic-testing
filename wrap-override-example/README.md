# Wrap override

Overriding of a certain symbol can be done by passing the `--wrap=symbol` to the linker; this works as-is for C, but for C++, functions and implementation (see [example10 - test1.cc](../ex/example10/tests/test1.cc)) all must be declared/included as `extern "C"` to prevent name mangling. A C++ implementation is still untested at the moment.
