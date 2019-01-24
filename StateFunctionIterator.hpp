/*
 * StateFunctionIterator.hpp - a state function iterator
 *
 * @created: Jan 7, 2017
 * @copyright: Copyright (c) 2017 Robert Zavalczki, distributed under the
 * terms and conditions of the WTFPL (http://www.wtfpl.net) license.
 */
#ifndef STATEFUNCTIONITERATOR_H_
#define STATEFUNCTIONITERATOR_H_

#include "concept/core_concepts.hpp"

#include <memory>   // addressof
#include <iterator> // iterator, input_iterator_tag
#include <tuple>    // tuple, tie


namespace iter_utils
{

/**
 * Iterate over applications of a state function: f : S -> (R, S)
 *
 * The increment operator applies the state function to the current state.
 * The dereference operator extracts the result of the function application.
 * The advantage is that the state handling is abstracted away, being handled
 * behind the scenes by the iterator.
 */
template<typename StateFunc, typename StateType, typename ResultType>
requires concept_check::EqualityComparable<StateType>() &&
         concept_check::Copyable<StateType>() &&
         concept_check::Copyable<ResultType>() &&
        /*
         * enforce a relation between the template parameters: namely that an
         * instance f of StateFunction can be called with a StateType parameter
         * returning a (ResultType, StateType) tuple, i.e.
         *     f : StateType -> (ResultType, StateType)
         */
         concept_check::Function<StateFunc, std::tuple<ResultType, StateType>, StateType>()
class StateFunctionIterator : public std::iterator<std::input_iterator_tag,
                                                   const ResultType>
{
private:
    ResultType result_;
    StateType state_;
    StateFunc stateFunc_;

public:
    using iterator = StateFunctionIterator;

    /**
     * Make a state function iterator from an initial state and an initial value
     *
     * Had we not had to provide the initial state, this would have looked like
     * the Monad 'unit' function (called 'return' in Haskell).
     */
    constexpr StateFunctionIterator(StateFunc stateFunc,
                                    const StateType &initialState,
                                    const ResultType &initialValue)
        : result_(initialValue), state_(initialState), stateFunc_(stateFunc)
    {
    }

    /**
     * Prefix increment operator, call the state function with the current state
     *
     * This is in a loose way similar to the Monad '>>=' (bind) function (from
     * Haskell), except that the function we 'bind' is fixed
     */
    iterator &operator++()
    {
        // let *this = *this >>= stateFunc_
        std::tie(result_, state_) = stateFunc_(state_);
        return *this;
    }

    /**
     * Iterator dereference (a.k.a. indirection) operator
     *
     * Extracts the result value from the iterator.
     */
    const ResultType &operator*() const
    {
        return result_;
    }

    /**
     * Iterator member of pointer operator
     *
     * Just obscure syntactic sugar for C programmers.
     */
    const ResultType *operator->() const
    {
        return std::addressof(result_);
    }

    /**
     * The iterator equivalence compares the state
     */
    bool operator==(const iterator &r) const
    {
        return !this->operator!=(r);
    }

    /**
     * The iterator equivalence compares the state
     */
    bool operator!=(const iterator &r) const
    {
        return state_ != r.state_;
    }
};

} /* namespace iter_utils */

#endif /* STATEFUNCTIONITERATOR_H_ */

