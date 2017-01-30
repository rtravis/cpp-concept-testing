# cpp-concept-testing - Experimenting with C++ Concepts

## Overview
Even though C++ 'concepts' have been around for 20 years, the concepts technical
specification ("Concepts TS") did not make it into the C++17 standard. Maybe
the next language standard - due in 2020 - will include it.

## Purpose of C++ Concepts
The intent of C++ concepts is to model semantic categories (Same, Number,
Function, Iterator etc.) rather than syntactic restrictions (Addable or
HasPlus). It also aims to make template programming more accessible by helping
the compiler provide human friendly template compilation error messages.

The syntactic constraints of concepts form a partially ordered set that
can be used by the compiler to derive the best candidate in overload resolution.

Unfortunately semantic constraints can't be considered in the ordering, so
that in order to do overload resolution using concepts that don't share a
relation in the syntactic constraints partial ordering, the compiler still needs
a hint from the programmer. For example the compiler would not know how to chose
between an overload for a 'ForwardIterator' and one for an 'InputIterator'. 

## Difference with Other Languages
C++ set up to depart from the "constrained genericity" present in Eiffel, Java,
C# or from the type classes of Haskell. All in all these solutions resort to
extra indirection (manipulate vtables) and the C++ philosophy abhors unnecessary
runtime costs. So as a consequence C++ concepts are checked at compile time and
do not incur any extra runtime costs.

## Compiler Support
As of January of 2017, the gcc compiler (version 6.1 or newer) includes
some support for the C++ concepts based on the specification in the:
"C++ Extensions for Concepts Technical Specification, ISO 19217 (2015)"
document. This support is enabled by providing the '-fconcepts' flag
to the compiler invocation.

## License
Copyright (c) 2017 Robert Zavalczki, distributed under the terms
and conditions of the WTFPL (http://www.wtfpl.net) license.

