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


namespace iter_utils
{

template<typename InputIterator>
struct IterRange
{
public:
    typedef InputIterator iterator;

    IterRange(iterator b, iterator e) :
            begin_{b}, end_{e}
    {
    }

    template<typename Container>
    explicit IterRange(const Container &c) :
            begin_{std::begin(c)}, end_{std::end(c)}
    {
    }

    ~IterRange() = default;
    IterRange(const IterRange&) = default;
    IterRange(IterRange&&) = default;
    IterRange &operator=(const IterRange&) = default;

    iterator begin() const
    {
        return begin_;
    }

    iterator end() const
    {
        return end_;
    }

    bool empty() const
    {
        return begin_ == end_;
    }

    bool operator==(const IterRange &r) const
    {
        return begin_ == r.begin_ && end_ == r.end_;
    }

    bool operator!=(const IterRange &r) const
    {
        return !operator==(r);
    }
private:
    iterator begin_;
    iterator end_;
};

} // namespace iter_utils

namespace test
{

/**
 * Example state function that tokenizes an iterator range into tokens
 *
 * The tokens are delimited by items for which the delimiter predicate holds.
 * The state is represented by (the remaining) string to be parsed. The result
 * is represented by the returned tokens.
 */
template <typename TokenDelimiterPredicate>
struct StringGetToken
{
private:
    TokenDelimiterPredicate isDelimiter_;

public:
    StringGetToken() : isDelimiter_{}
    {
    }

    template <typename InputIterator>
    auto operator()(const iter_utils::IterRange<InputIterator> &r)
    {
        typedef iter_utils::IterRange<InputIterator> Range;

        InputIterator b = r.begin();
        const InputIterator e = r.end();

        // make 'b' point to the first non-separator character
        while (b != e && isDelimiter_(*b)) {
            ++b;
        }

        InputIterator i = b;

        // make 'i' point to the next separator after 'b'
        while (i != e && !isDelimiter_(*i)) {
            ++i;
        }

        return std::make_tuple(Range{b, i}, Range{i, e});
    }
};

struct WordsDelimiter
{
    bool operator()(char c)
    {
        return !isalnum(c);
    }
};

typedef iter_utils::IterRange<const char*> TextRange;
using TokensIterator = iter_utils::StateFunctionIterator<
                                       StringGetToken<WordsDelimiter>,
                                       TextRange, TextRange>;


/**
 * 'newtype' to wrap a TextRange and to provide a tokens view of an iterator range
 */
class TextTokenizer
{
public:
    TextTokenizer(const TextRange &r) : textRange_{r}
    {
    }

    TokensIterator begin() const
    {
        return ++TokensIterator{textRange_, TextRange{nullptr, nullptr}};
    }

    TokensIterator end() const
    {
        return TokensIterator{TextRange{textRange_.end(), textRange_.end()},
                              TextRange{nullptr, nullptr}};
    }

private:
    TextRange textRange_;
};

} // namespace test

namespace iter_utils
{

std::ostream &operator<<(std::ostream &os, const test::TextRange &r)
{
    return os.write(r.begin(), r.end() - r.begin());
}

}

int main(int, char*[])
{
    const char text[] = R"(
        This text will be split into tokens.)";

    test::TextTokenizer tokenizer{test::TextRange{text}};

    std::copy(tokenizer.begin(), tokenizer.end(),
            std::ostream_iterator<const test::TextRange&>(std::cout, "\n"));

}

