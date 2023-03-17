#include "play_game.hpp"

#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "game_objects.hpp"
#include "leaderboard.hpp"

namespace krv {


    

bool play_game(sf::RenderWindow &window, const std::string &filename) {
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(24.0f, 18.0f));
    sf::Font arial;
    arial.loadFromFile("../pic/text/arial.ttf");
    window.setView(view);
    LeaderBoard leaderboard(filename.substr(0, filename.size() - 4) + "_scores.txt");
    Game_Objects game_objects(window, LEVEL_SELECTION_TYPE::PLAY, filename);
    sf::Clock clock;
    sf::Text time_text("0", arial);
    unsigned long long time = 0;

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
            time += static_cast<unsigned long long>(d_time*1000.0f);
            time_text.setString(std::to_string(time/1000) + "." + std::to_string(time%1000));

            view.move(sf::Vector2f((game_objects.get_player_pos() - view.getCenter()))*(4.0f*d_time));
            window.setView(view);

            game_objects.update(d_time);

            window.clear();
            window.draw(game_objects);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                window.draw(leaderboard);
            }
            window.setView(window.getDefaultView());
            window.draw(time_text);
            window.setView(view);
            window.display();
        }

        //Post update and draw logic (death and finish events)
        if (game_objects.player_death()) {
            window.setView(window.getDefaultView());
            return false;
        }
        if (game_objects.player_finish()) {
            window.setView(window.getDefaultView());
            leaderboard.save(window, time);
            return true;
        }
    }

    window.setView(window.getDefaultView());
    return true;
}




}