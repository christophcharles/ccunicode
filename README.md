# ccunicode

## What is ccunicode ?

ccunicode is a small single-header C library to help conversion between utf-8, utf-16 and codepoints. It provides a list of functions that can convert null-terminated strings into list of codepoints, list of codepoints into utf-8 and utf-16 strings or directly convert between utf-8 and utf-16.

Please refer to the doxygen documentation for more details.

## How to use ccunicode ?

ccunicode is a header-only library. Just copy the single include file into your project. Add a C (not C++) source file into your project and define the macro __CCUNICODE_IMPL__ before including the header in this C file. This will trigger the implementation of the various functions into your C file. You can look at src/ccunicode.c for an example of such a file.

You can also define the macro __CCUNICODE_NOSTDALLOC__ in your C file (beofre including). This will prevent ccunicode to link with the standard library for allocations. You will need however to provide systematically your own allocations functions if ccunicode requires memory allocations. It is not necessary but it is recommended to also define __CCUNICODE_NOSTDALLOC__ before including in your other source files. This will prevent the declaration of some ccunicode functions that would otherwise result in linking error if misused.

## Licensing

ccunicode protected byt the MIT license which is pretty liberal. Please refer to the LICENSE file for more details.

## Tests

ccunicode comes with a very small test suite. You can use it on pretty much any environment, as long as it is compatible with cmake. On Unix like:

```console
> mkdir build
> cd build
> cmake ..
> make test
```
