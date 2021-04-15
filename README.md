# EnumPP
C++ enums with introspection (and hence string conversion and value checking).

## Summary

Enum++ enhances C++'s weak enums (especially C++03 and earlier) by providing introspection, (string) conversion, and value checking functionality using a single macro that handles all the code generation using just the preprocessor without any unnecessary boilerplate, meta-compilation, or other non-standard shennanigans.

Check out enum_pp_demo.cpp to see it in use.

## Dependencies

* CMake 3.0 or newer
* Boost Preprocessor library (only headers, sufficiently recent version (say 1.57 or newer))
* C++11 (though it can be made to work with C++03 and older with just a few minor drawbacks)
* Variadic Macros enabled in compiler (see CMakefile)

## History/Bragging

I actually implemented the first version of Enum++ in 2012 before any of the "better enum" solutions existed out there
(or at least before they could be found via Google). With the advent of C++11's scoped enums, I was able to overcome the last major design limitation, thus giving rise to the library as it is today, usable as a drop-in replacement wherever normal enums can be used (namespaces, nested in classes, ...)
