/*
 * tester.cpp - tester program
 *
 * @created: Feb 5, 2017
 * @copyright: Copyright (c) 2017 Robert Zavalczki, distributed under the
 * terms and conditions of the WTFPL (http://www.wtfpl.net) license.
 */
#include "StateFunctionIterator.hpp"

#include <cctype>
#include <iostream>
#include <iterator> // std::begin, end
#include <string_view>


namespace test
{

/**
 * a contiguous range of char-s
 */
struct TextRange : public std::string_view
{
    constexpr TextRange(iterator b, iterator e)
        : std::string_view(b, static_cast<size_t>(std::distance(b, e)))
    {
    }

    constexpr TextRange(const std::string_view &sv) : std::string_view(sv)
    {
    }
};

/**
 * get the span of elements for which a predicate does not hold
 *
 * \param r the source range
 * \param pred predicate that determines which items are excluded from the span
 * \return the tuple: (`span`, `rest`) where `span` is a contiguous range of
 *  elements for which the predicate does *not* hold and `rest` is the
 *  remaining part of the range
 */
template <typename Range, typename Predicate>
std::tuple<Range, Range> complementarySpan(const Range &r, Predicate pred)
{
    auto b = std::cbegin(r);
    auto const e = std::cend(r);

    // make 'b' point to the first non-separator character
    while (b != e && pred(*b)) {
        ++b;
    }

    auto i = b;

    // make 'i' point to the next separator after 'b'
    while (i != e && !pred(*i)) {
        ++i;
    }

    return std::make_tuple(Range{b, i}, Range{i, e});
}

/**
 * A state function that parses a string and extracts the first token (word)
 *
 * \remark Tokens are delimited by one ore more non-alphanumeric characters.
 *  The state is represented by (the remaining) string to be parsed.
 */
static auto getFirstWordAndTheRest(const TextRange &r)
{
    auto isDelimiter = [](char c) {
                            return !isalnum(
                                        static_cast<unsigned char>(c));
                        };
    return complementarySpan(r, isDelimiter);
}

/**
 * 'newtype' to wrap a TextRange and to provide a tokens view of it
 */
class TokensView
{
public:
    using StateFunction = decltype(&getFirstWordAndTheRest);
    using State = TextRange;
    using Result = TextRange;
    using TokenIterator = iter_utils::StateFunctionIterator<
                                        StateFunction,
                                        State, Result>;

    explicit TokensView(const TextRange &r) : textRange_{r}
    {
    }

    TokenIterator begin() const
    {
        // increment the first time to move to the first word
        return ++TokenIterator{&getFirstWordAndTheRest, textRange_,
                               TextRange{nullptr, nullptr}};
    }

    TokenIterator end() const
    {
        return TokenIterator{&getFirstWordAndTheRest,
                             TextRange{textRange_.end(), textRange_.end()},
                             TextRange{nullptr, nullptr}};
    }

private:
    TextRange textRange_;
};

} // namespace test

int main(int, char*[])
{
    const char text[] = R"(
        This text will be split into alpha-numeric only tokens.)";

    test::TokensView tokenizer{std::string_view{text}};

    std::copy(tokenizer.begin(), tokenizer.end(),
            std::ostream_iterator<const test::TextRange&>(std::cout, "\n"));

}

