#include "words.hpp"
#include <array>
#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>

using namespace std::chrono_literals;

enum class TypeSpeed {
    normal,
    slow,
    instant
};

void typeString(std::string_view text, TypeSpeed typeSpeed = TypeSpeed::normal) {
    for (const auto& c: text) {
        if constexpr (!typeFast) {
            if (typeSpeed != TypeSpeed::instant) {
                std::this_thread::sleep_for(((typeSpeed == TypeSpeed::normal)?50ms:200ms));
            }
        }
        std::cout << c;
    }
}

void typeCurrentFoodList(size_t food, size_t adjective, bool capitalFirst = false) {
    for (size_t curFood {0}, curAdjective {0}; curFood < food || curAdjective <= adjective;) {
        if (curAdjective == adjectives.size()) {
            curAdjective = 0;
            ++curFood;
        }

        if (curFood == 0 && curAdjective == 0) {
            if (capitalFirst) {
                typeString("B");
            } else {
                typeString("b");
            }
            typeString("read");
        } else {
            typeString(", ");
            typeString(foods[curFood]);
            typeString(adjectives[curAdjective]);
        }

        ++curAdjective;
    }
}

void printFood() {
    typeString("\n\a\t\tBREAD, CAN I GO WITH YOU\?\n", TypeSpeed::instant);
    typeString("\tBread goes on and meets bread with butter, who says \"Bread, can I go with you\?\", to which bread replies: \"Yeah, you can.\"\n");

    for (size_t curFood {0}, curAdjective {1}; true;) {
        bool lastResp {curFood == foods.size() - 1 && curAdjective == adjectives.size() - 1};
        

        typeString("\tAnd so ");
        typeCurrentFoodList(curFood, curAdjective);
        typeString(", go on and meet ");
        
        if (lastResp) {
            typeString("tomato");
            typeString("");
        } else if (curAdjective == adjectives.size() - 1) {
            typeString(foods[curFood + 1]);
            typeString(adjectives[0]);
        } else {
            typeString(foods[curFood]);
            typeString(adjectives[curAdjective + 1]);
        }

        typeString(", who says \"");
        typeCurrentFoodList(curFood, curAdjective, true);
        typeString(", can I go with you\?\", to which ");
        typeCurrentFoodList(curFood, curAdjective);

        if (lastResp) {
            typeString(", \areply: \"");
            if constexpr (!typeFast) {
                typeString("Yeah, you ca");
                std::this_thread::sleep_for(1500ms);
                for (int i {0}; i < 12; ++i) {
                    std::this_thread::sleep_for((200ms));                
                    std::cout << "\b \b";
                }
            }
            typeString("No.\"\n", TypeSpeed::slow);
            break;

        } else {
            typeString(", reply: \"Yeah, you can.\"\n");
            if (++curAdjective == 3) {
                curAdjective = 0;
                ++curFood;
            }
        }
    }
    
}

int main() {
    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    printFood();
    const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

    std::chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "\nThe story took " << duration / 1s << "s.\n";

    std::cin.get();
    return 0;
}