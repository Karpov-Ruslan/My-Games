#pragma once

#include <SFML/Graphics.hpp>
#include "menu_components.hpp"
#include "background.hpp"
#include "level_selection_menu.hpp"

namespace krv {


void game_menu() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Glider", sf::Style::Close);
    window.setFramerateLimit(144);

    sf::Image cursor_image;
    cursor_image.loadFromFile("../pic/Glider/cursor.png");
    sf::Cursor cursor;
    cursor.loadFromPixels(cursor_image.getPixelsPtr(), sf::Vector2u(7, 7), sf::Vector2u(3, 3));
    window.setMouseCursor(cursor);


    sf::Texture background_texture;
    background_texture.loadFromFile("../pic/Glider/main_menu_background.png");
    Background background(window, background_texture);


    sf::Texture main_menu_buttons_texture;
    main_menu_buttons_texture.loadFromFile("../pic/Glider/main_menu_buttons.png");

    Quadratic_Button play_button(400.0f, 500.0f, 100.0f, main_menu_buttons_texture, 2.0f);
    play_button.setTextureRect(sf::IntRect(0, 0, 50, 50));

    Quadratic_Button exit_button(550.0f, 500.0f, 100.0f, main_menu_buttons_texture);
    exit_button.setTextureRect(sf::IntRect(0, 100, 50, 50));

    Quadratic_Button build_button(250.0f, 500.0f, 100.0f, main_menu_buttons_texture, 3.0f);
    build_button.setTextureRect(sf::IntRect(0, 50, 50, 50));

    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (exit_button.mouse_on(window)) {
                    window.close();
                }
                if (play_button.mouse_on(window)) {
                    level_selection_menu(window, LEVEL_SELECTION_TYPE::PLAY);
                }
                if (build_button.mouse_on(window)) {
                    level_selection_menu(window, LEVEL_SELECTION_TYPE::BUILD);
                }
            }
        }
        play_button.shading(window);
        exit_button.shading(window);
        build_button.shading(window);



        window.clear();
        window.draw(background);
        window.draw(play_button);
        window.draw(exit_button);
        window.draw(build_button);
        window.display();
    }

    return;
}





}