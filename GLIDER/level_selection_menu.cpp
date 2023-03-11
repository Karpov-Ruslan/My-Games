#include <SFML/Graphics.hpp>
#include <cmath>
#include "menu_components.hpp"
#include "build_menu.hpp"
#include "play_game.hpp"
#include "level_selection_menu.hpp"

namespace krv {

    void level_selection_menu(sf::RenderWindow &window, LEVEL_SELECTION_TYPE level_selection_menu) {
    File_List file_list("../levels/levels.txt", 450.0f, 25.0f, 700.0f, 40.0f, 50.0f);
    Scrollbar scrollbar(file_list.size(), 12, 85.0f, 300.0f, 10.0f, 590.0f);

    sf::Texture level_menu_buttons_texture;
    level_menu_buttons_texture.loadFromFile("../pic/level_menu_buttons.png");
    LevelSelectionCursor cursor(450.0f, 0.0f, 700.0f, 40.0f, level_menu_buttons_texture);
    cursor.delete_button.setTextureRect(sf::IntRect(0, 100, 50, 50));

    std::vector<Quadratic_Button> buttons_array; // [0] - exit_button // [1] - create_level_button //
    buttons_array.push_back(Quadratic_Button(40.0f, 565.0f, 60.0f, level_menu_buttons_texture));
    buttons_array[0].setTextureRect(sf::IntRect(0, 50, 50, 50));
    
    if (level_selection_menu == LEVEL_SELECTION_TYPE::BUILD) {
        cursor.set_draw_delete_button(true);
        buttons_array.push_back(Quadratic_Button(40.0f, 35.0f, 60.0f, level_menu_buttons_texture, 3));
        buttons_array[1].setTextureRect(sf::IntRect(0, 0, 50, 50));
    }


    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (buttons_array[0].mouse_on(window)) {
                    return;
                }
                if (buttons_array[1].mouse_on(window)) {
                    file_list.add_level(window, scrollbar);
                }
                if (cursor.delete_button.mouse_on(window) && level_selection_menu == LEVEL_SELECTION_TYPE::BUILD) {
                    file_list.delete_level(window, scrollbar, cursor);
                }
                else if (cursor.get_mouse_iterator() != file_list.end()) {
                    if (level_selection_menu == LEVEL_SELECTION_TYPE::BUILD) {
                        build_menu(window, file_list.levels_folder + static_cast<std::string>(cursor.get_mouse_iterator()->text.getString()) + ".txt");
                    }
                    if (level_selection_menu == LEVEL_SELECTION_TYPE::PLAY) {
                        window.setMouseCursorVisible(false);
                        while (!play_game(window, file_list.levels_folder + static_cast<std::string>(cursor.get_mouse_iterator()->text.getString()) + ".txt"));
                        window.setMouseCursorVisible(true);
                    }
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                int delta = static_cast<int>((event.mouseWheelScroll.delta)/(std::abs(event.mouseWheelScroll.delta)));
                scrollbar.change_scroll_position(scrollbar.get_upper_element_number() - delta);
                file_list.change_upper_visible_element(file_list.get_upper_visible_element_number() - delta);
            }
        }

        cursor.delete_button.shading(window);
        for (int i = 0; i < buttons_array.size(); i++) {
            buttons_array[i].shading(window);
        }
        cursor.set_mouse_on(file_list.mouse_on(window), file_list);



        window.clear();
        window.draw(file_list);
        window.draw(scrollbar);
        for (int i = 0; i < buttons_array.size(); i++) {
            window.draw(buttons_array[i]);
        }
        window.draw(cursor);
        window.display();
        //std::cout << file_list.size() << std::endl;
    }

}

}