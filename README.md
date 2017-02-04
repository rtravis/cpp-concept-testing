# cpp-concept-testing - Experimenting with C++ Concepts

## Overview
A concept is an abstract or general idea inferred or derived from specific
instances. This is the defintion of a concept according to WordNet 3.0 (2006).
In contrast a C++ concept is a predicate that defines syntactic and semantic
requirements on type parameters (template arguments).

Even though C++ 'concepts' have been around for 20 years, the concepts technical
specification ("Concepts TS") did not make it into the C++17 standard. Maybe
the next language standard - due in 2020 - will include it.

## Purpose of C++ Concepts
The intent of C++ concepts is to model semantic categories (Same, Number,
Function, Iterator etc.) rather than syntactic restrictions (Addable or
HasPlus). The aim is to make template programming more accessible by helping
the compiler provide human friendly template compilation error messages.

The syntactic constraints of concepts form a partially ordered set that
can be used by the compiler to derive the best candidate in overload resolution.

Semantic constraints can't be considered during overload resolution using
concepts (because they don't contribute in the concepts partial ordering) so in
cases of ambiguity the compiler still needs a hint from the programmer. For
example both 'ForwardIterator' and 'InputIterator' have the same syntactic
constraints, but semantically only the 'ForwardIterator' has the 'multipass'
property.

## Difference with Other Languages
C++ set up to depart from the "constrained genericity" present in Eiffel, Java,
C# or from the type classes of Haskell. The solutions used by these languages
resort to manipulating vtables (require extra indirection) thus contravening
the C++ philosophy which abhors unnecessary runtime costs. As a consequence,
C++ concepts are checked at compile time only and incur no runtime costs.

## Compiler Support
As of January of 2017, the gcc compiler (version 6.1 or newer) includes
some support for the C++ concepts based on the specification in the:
"C++ Extensions for Concepts Technical Specification, ISO 19217 (2015)"
document. This support is enabled by providing the '-fconcepts' flag
to the compiler invocation.

## License
Copyright (c) 2017 Robert Zavalczki, distributed under the terms
and conditions of the WTFPL (http://www.wtfpl.net) license.

