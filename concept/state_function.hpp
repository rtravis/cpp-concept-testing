/*
 * state_function.hpp - definition of a simple state function concept
 *
 * @created: Feb 4, 2017
 * @copyright: Copyright (c) 2017 Robert Zavalczki, distributed under the terms
 * and conditions of the WTFPL (http://www.wtfpl.net) license.
 */
#ifndef STATE_FUNCTION_CONCEPT_HPP__
#define STATE_FUNCTION_CONCEPT_HPP__

#include <tuple>


namespace concept_check
{

/**
 * Declaration of the concept "StateFunction", which is satisfied by any
 * function f of type F, state s of type S and result r of type R such that
 * the expression f(s) compiles and its result is convertible to tuple<R, S>
 * Or in pseudo-math: f : S -> (R, S)
 */
template<typename F, typename S, typename R>
concept bool StateFunction() {
	return requires(F f, S s, R r) {
		{ f(s) } -> std::tuple<R, S>;
	};
}

} /* namespace concept_check */

#endif /* STATE_FUNCTION_CONCEPT_HPP__ */

