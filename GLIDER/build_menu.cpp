#include <SFML/Graphics.hpp>
#include <iostream>
#include "build_menu.hpp"
#include "menu_components.hpp"
#include "build_components.hpp"

namespace krv {

class MyMouse : public sf::Mouse {
    sf::Vector2i coords;
    float factor = 0.03f;
  public:
    sf::Vector2i update(sf::RenderWindow &window) {
        sf::Vector2i vec = coords;
        coords = sf::Mouse::getPosition(window);
        return coords - vec;
    }

    float get_factor() {
        return factor;
    }

    void zoom(float x) {
        factor = factor*x;
    }
};



void build_menu(sf::RenderWindow &window, const std::string &level_file) {
    Game_Objects game_objects;
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(24.0f, 18.0f));
    window.setView(view);
    MyMouse mouse;
/////////////////////////>   Moving Elements   <//////////////////////////////////
    Build_Cursor build_cursor(1.0f);
/////////////////////////>   Static Elements   <//////////////////////////////////
    Build_Type build_type;
    // sf::RectangleShape game_object_type(sf::Vector2f());
    // game_object_type.set


    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2f delta = static_cast<sf::Vector2f>(mouse.update(window))*mouse.get_factor();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                    view.move(-delta);
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (build_cursor.get_pressed()) {
                        build_cursor.change_press();
                    }
                    else {
                        window.setView(window.getDefaultView());
                        return;
                    }
                }
                if (event.key.code == sf::Keyboard::Space) {
                    view.setCenter(0.0f, 0.0f);
                    window.setView(view);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    if (build_cursor.get_pressed()) {
                        game_objects.add(window, build_cursor.get_type(), build_cursor.get_floatrect(), build_cursor.get_rotation());
                    }
                    //TODO:
                    // if (build_cursor.get_type() == GAME_OBJECT_TYPE::NOTHING) {

                    // }
                    build_cursor.change_press();
                }
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    build_cursor.rotate();
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                //Change scale
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    if (event.mouseWheelScroll.delta > 0.0f) {
                        if (mouse.get_factor() > 0.003f) {
                            float x = 1.0f/1.1f;
                            view.zoom(x);
                            mouse.zoom(x);
                        }
                    }
                    if (event.mouseWheelScroll.delta < 0.0f) {
                        if (mouse.get_factor() < 1.0f) {
                            float x = 1.1f;
                            view.zoom(x);
                            mouse.zoom(x);
                        }
                    }
                }
                else {
                    if (event.mouseWheelScroll.delta > 0.0f) {
                        build_cursor.decrease_type();
                    }
                    else if (event.mouseWheelScroll.delta < 0.0f) {
                        build_cursor.increase_type();
                    }
                    build_type.update(build_cursor.get_type());
                }
            }
            build_cursor.update(window, view);
        }


/////////////////////////>   Moving Elements   <//////////////////////////////////
        window.setView(view);
        window.clear(sf::Color(50, 75, 75, 255));

        window.draw(game_objects);

        window.draw(build_cursor);
/////////////////////////>   Static Elements   <//////////////////////////////////
        window.setView(window.getDefaultView());

        window.draw(build_type);

        window.display();
    }
}


}