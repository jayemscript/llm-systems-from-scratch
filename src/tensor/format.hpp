//tensor/format.hpp
#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <fmt/format.h>

// writes output as repeated character
template <typename OutputIterator>
void repeat(OutputIterator write, const char ch, std::size_t count) {
    for (std::size_t i = 0; i < count; i++) {
        fmt::format_to(write, "{}", ch);
    }
}



#endif