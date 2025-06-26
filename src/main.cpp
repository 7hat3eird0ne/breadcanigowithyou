#include "words.hpp"
#include <array>
#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>

using namespace std::chrono_literals;


void typeString(std::string_view text, bool typeSlow = false) {
    char c {};
    for (size_t i {0}; i < text.length(); ++i) {
        c = text[i];
        if constexpr (!typeFast) {
            std::this_thread::sleep_for((typeSlow?200ms:50ms));
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

    /*
    adjective incremented at the end of every round
    then if adjective = adjectives.size(), food incremented

    next loop continues only if food is still below the target food OR the adjective is below (or equal to) target adjective, 
    meaning that if the loop is supposed to reach new food, then it relies on the adjectives, which at the start of loop are equal to what is meant to print 
    (meaning that since target adjective is supposed to be print too, <= is required) if the adjective target is 2, then it continues through 2 and then once it becomes 3 it fails

    therefore 3 is reset to 0 at the START of the loop, so that it can be properly removed
    
    */
}

void printFood() {
    std::cout << "\a        BREAD, CAN I GO WITH YOU\?\n";
    typeString("  Bread goes on and meets bread with butter, who says \"Bread, can I go with you\?\", to which bread replies \"Yeah, you can.\"\n");

    for (size_t curFood {0}, curAdjective {1}; true;) {
        bool lastResp {curFood == foods.size() - 1 && curAdjective == adjectives.size() - 1};
        

        typeString("  And so ");
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
            typeString(", reply \"");
            if constexpr (!typeFast) {
                typeString("Yeah.\"");
                std::this_thread::sleep_for(800ms);
                for (int i {0}; i < 6; ++i) {
                    std::this_thread::sleep_for((200ms));                
                    std::cout << "\b \b";
                }
            }
            typeString("No\"\n", true);
            break;

        } else {
            typeString(", reply \"Yeah, you can.\"\n");
            if (++curAdjective == 3) {
                curAdjective = 0;
                ++curFood;
            }
        }
    }
    
}

int main() {
    printFood();

    std::cin.get();
    return 0;
}