#pragma once

#include <SFML/Graphics.hpp>

namespace krv {

void remove_begin_end_spaces(std::string &string) {
    while (string[0] == ' ') {
        string.erase(string.begin());
    }
    while (string[string.size() - 1] == ' ') {
        string.erase(--string.end());
    }
}

std::string const_remove_begin_end_spaces(const std::string &string) {
    std::string str = string;
    remove_begin_end_spaces(str);
    return str;
}

class MyFont : public sf::Font {
  public:
    MyFont(const std::string &filename) : Font() {
        loadFromFile(filename);
    }
};




}