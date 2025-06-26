#ifndef WORDS_HPP
#define WORDS_HPP
    
#include <array>
#include <string_view>

constexpr std::array<std::string_view, 25> foods {
    "bread",
    "roll",
    "bun",
    "baguette",
    "cross bun",
    "croissant",
    "cracker",
    "Christmas cake",
    "pretzel",
    "Kaiser roll",
    "sponge biscuit",
    "French bread",
    "pancake",
    "crepe",
    "cake",
    "doughnut",
    "brioche",
    "braided bun",
    "puff pastry pocket",
    "Chinese fortune cookies",
    "langos",
    "Easter lamb",
    "wafer",
    "waffle",
    "toast",
};

constexpr std::array<std::string_view, 3> adjectives {
    "",
    " with butter",
    " with butter and sausage",
};

#endif