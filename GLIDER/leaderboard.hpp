#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace krv {

    class LeaderBoard : public sf::Drawable {
        sf::RectangleShape background;
        sf::Text leaders_table;
        sf::Text scores_table;
        std::vector<std::pair<std::string, unsigned long long>> leader_board;
        sf::Font arial;
        const std::string filename;

    public:
        LeaderBoard(const std::string &filename);

        void load();

        void save(sf::RenderWindow &window, long long time);

        void print_scores();

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

}