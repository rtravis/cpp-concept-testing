/*
 * core_concepts.hpp - definition of core concepts used in the examples
 *
 * @created: Jan 7, 2017
 * @copyright: Copyright (c) 2017 Robert Zavalczki, distributed under the terms
 * and conditions of the WTFPL (http://www.wtfpl.net) license.
 */
#ifndef CORE_CONCEPTS_HPP_
#define CORE_CONCEPTS_HPP_

namespace concept_check
{

/**
 * Definition of the concept "Function" which is satisfied by any type F such
 * that for an f of type F the expression f(Args...) is valid and yields a
 * result convertible to R.
 */
template<typename F, typename R, typename ...Args>
concept bool Function() {
    return requires(F f, Args... args) {
        { f(args...) } -> R;
    };
}

/**
 * Definition of the concept "EqualityComparable" which is satisfied by any
 * type T such that for any a, b of type T the expression a == b is valid and
 * yields a result convertible to bool.
 *
 * \remark semantically the '==' function should be an equivalence relation, but
 * we can't enforce that here.
 */
template<typename T>
concept bool EqualityComparable() {
    return requires(T a, T b) {
        { a == b } -> bool;
        { a != b } -> bool;
        /*
         * Axiom checking is not currently included in the ISO
         * axiom { a == b <=> eq(a, b); }
         * axiom {
         *  a == a;
         *  a == b => b == a;
         *  a == b && b == c => a == c;
         *}
         * axiom { a != b <=> !(a == b) }
         */
    };
}

template<typename T>
concept bool CopyConstructible() {
    return requires(const T &a) {
        { T(a) } -> T;
    };
}

template<typename T>
concept bool CopyAssignable() {
    return requires(T a, const T &b) {
        { a = b } -> T&;
    };
}

/*
 * This is a simple example that shows how more concepts can be
 * combined to form more complex concepts
 */
template<typename T>
concept bool Copyable() {
    return CopyConstructible<T>() && CopyAssignable<T>();
}

} /* namespace concept_check */

#endif /* CORE_CONCEPTS_HPP_ */
