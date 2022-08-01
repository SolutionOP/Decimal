# s21_decimal 

## Part 1. Implementation of the decimal.h library functions

The functions of the decimal.h library described [above](#information) must be implemented:
- The library must be developed in C language of C11 standard using gcc compiler
- The library code must be located in the src folder on the develop branch   
- Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard.
- Make it as a static library (with the s21_decimal.h header file)
- The library must be developed according to the principles of structured programming;
- Use prefix s21_ before each function
- Prepare full coverage of library functions code with unit-tests using the Check library
- Unit tests must cover at least 80% of each function (checked using gcov)   
- Provide a Makefile for building the library and tests (with targets all, clean, test, s21_decimal.a, gcov_report)  
- The gcov_report target should generate a gcov report in the form of an html page. Unit tests must be run with gcov flags to do this
- When implementing decimal, stick to [the binary representation](#binary-representation) with the integer `bits` array as specified in the [example above](#example). Observe the position of the digits of a number in the `bits` array
- It is forbidden to use the __int128 type
- Trailing zeros can be as preserved as deleted (except for the `s21_truncate` function)
- The defined type must support numbers from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.
