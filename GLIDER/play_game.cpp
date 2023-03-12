#include "play_game.hpp"

#include <SFML/Graphics.hpp>
#include "game_objects.hpp"

namespace krv {


    

bool play_game(sf::RenderWindow &window, const std::string &filename) {
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(24.0f, 18.0f));
    window.setView(view);
    Game_Objects game_objects(window, LEVEL_SELECTION_TYPE::PLAY, filename);
    sf::Clock clock;

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

        float d_time = clock.getElapsedTime().asSeconds();
        clock.restart();
        if (d_time < 0.05f) {
            view.move(sf::Vector2f((game_objects.get_player_pos() - view.getCenter()))*(d_time*2.0f));
            window.setView(view);

            game_objects.update(d_time);

            window.clear();
            window.draw(game_objects);
            window.display();
        }

        //Post update and draw logic (death and finish events)
        if (game_objects.player_death()) {
            window.setView(window.getDefaultView());
            return false;
        }
        if (game_objects.player_finish()) {
            window.setView(window.getDefaultView());
            return true;
        }
    }

    window.setView(window.getDefaultView());
    return true;
}




}