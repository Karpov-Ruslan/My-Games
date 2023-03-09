#include "play_game.hpp"

#include <SFML/Graphics.hpp>
#include <thread>
#include "game_objects.hpp"

namespace krv {


    

bool play_game(sf::RenderWindow &window, const std::string &filename) {
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(24.0f, 18.0f));
    window.setView(view);
    Sky sky(window);
    Game_Objects game_objects(window, LEVEL_SELECTION_TYPE::PLAY, filename);
    sf::Clock d_time;
    long long world_time;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.setView(window.getDefaultView());
                    return true;
                }
            }
        }

        d_time.restart();




        window.clear();
        
        window.display();
    }

    window.setView(window.getDefaultView());
    return true;
}




}