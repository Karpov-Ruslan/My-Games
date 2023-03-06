#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <string>
#include <cstdio>
#include "menu_components.hpp"
#include "stuff.hpp"

namespace krv {

    bool consent_window(sf::RenderWindow &window, const std::string& txt) {
        static MyFont arial("../pic/text/arial.ttf");
        sf::Text text(txt, arial, 75);
        text.setOrigin(text.getLocalBounds().width/2.0f, 0.0f);
        text.setPosition(400.0f, 200.0f);
        sf::Texture buttons_texture;
        buttons_texture.loadFromFile("../pic/yesno.png");
        Quadratic_Button button_yes(320.0f, 370.0f, 100.0f, buttons_texture, 2.0f);
        button_yes.setTextureRect(sf::IntRect(0, 0, 50, 50));
        Quadratic_Button button_no(480.0f, 370.0f, 100.0f, buttons_texture);
        button_no.setTextureRect(sf::IntRect(0, 50, 50, 50));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (button_yes.mouse_on(window)) {
                        return true;
                    }
                    if (button_no.mouse_on(window)) {
                        return false;
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        return true;
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        return false;
                    }
                }
            }


            button_yes.shading(window);
            button_no.shading(window);

            window.clear();
            window.draw(button_yes);
            window.draw(button_no);
            window.draw(text);
            window.display();
        }

        return false;
    }

    Quadratic_Button::Quadratic_Button(const float pos_x, const float pos_y, const float length, const float n) : n(n) {
        setPosition(pos_x, pos_y);
        setOrigin(length/2.0f, length/2.0f);
        setSize(sf::Vector2f(length, length));
    }

    Quadratic_Button::Quadratic_Button(const float pos_x, const float pos_y, const float length, const sf::Texture &texture, const float n) : n(n) {
        setPosition(pos_x, pos_y);
        setOrigin(length/2.0f, length/2.0f);
        setSize(sf::Vector2f(length, length));
        setTexture(&texture);
    }

    bool Quadratic_Button::mouse_on(const sf::RenderWindow &window) const {
        if (std::isnormal(n)) {
            return ((getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))&&( pow(abs(sf::Mouse::getPosition(window).x - getPosition().x), n) + pow(abs(sf::Mouse::getPosition(window).y - getPosition().y), n) < pow(getOrigin().x, n) ));
        }

        else {
            return getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        }
    }

    void Quadratic_Button::shading(const sf::RenderWindow &window) {
        if (mouse_on(window)) {
            setFillColor(sf::Color(200, 200, 200, 255));
        }
        else {
            setFillColor(sf::Color::White);
        }
    }

    Text_Button::Text_Button(const std::string &text_string, const float pos_x, const float pos_y, const float width, const float height, const ALIGNMENT_TYPE alignment_type, const sf::Color color) {
        static MyFont arial("../pic/text/arial.ttf");
        text.setFont(arial);
        text.setString(text_string);
        text.setCharacterSize(static_cast<unsigned int>(0.75f*height));
        sf::FloatRect text_rect = text.getLocalBounds();
        switch (alignment_type) {
            case ALIGNMENT_TYPE::LEFT: {
                text.setOrigin(0.0f, 0.0f);
                text.setPosition(pos_x - width/2.1f, pos_y - height/2.0f);
                break;
            }
            case ALIGNMENT_TYPE::CENTER: {
                text.setOrigin(text_rect.width/2.0f, 0.0f);
                text.setPosition(pos_x, pos_y - height/2.0f);
                break;
            }
            case ALIGNMENT_TYPE::RIGHT: {
                text.setOrigin(text_rect.width, 0.0f);
                text.setPosition(pos_x + width/2.2f, pos_y - height/2.0f);
                break;
            }
        }

        background.setPosition(pos_x, pos_y);
        background.setSize(sf::Vector2f(width, height));
        background.setOrigin(width/2.0f, height/2.0f);
        background.setFillColor(color);
    }

    void Text_Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(background, states);
        target.draw(text, states);
    }

    Scrollbar::Scrollbar(const int total_elements_number, const int visible_elements_number, const float pos_x, const float pos_y, const float width, const float height, const sf::Color bar_color, const sf::Color scroll_color) : total_elements_number(total_elements_number), visible_elements_number(visible_elements_number), upper_element_number(1), top(pos_y - height/2.0f), height(height) {
        bar.setPosition(pos_x, pos_y);
        bar.setOrigin(width/2.0f, height/2.0f);
        bar.setSize(sf::Vector2f(width, height));
        bar.setFillColor(bar_color);

        scroll.setFillColor(scroll_color);
        scroll.setOrigin(width/2.0f, 0.0f);
        scroll.setPosition(pos_x, top);
        if (total_elements_number <= visible_elements_number) {
            scroll.setSize(sf::Vector2f(width, height));
        }
        else {
            scroll.setSize(sf::Vector2f(width, (static_cast<float>(visible_elements_number)/static_cast<float>(total_elements_number))*height));
        }
    }

    void Scrollbar::change_scroll_position(const int new_upper_element_number) {
        if (total_elements_number > visible_elements_number && new_upper_element_number <= total_elements_number - visible_elements_number + 1 && new_upper_element_number > 0) {
            upper_element_number = new_upper_element_number;
            scroll.setPosition(scroll.getPosition().x, top + (static_cast<float>(new_upper_element_number - 1)/static_cast<float>(total_elements_number - visible_elements_number))*(height - scroll.getSize().y));
        }
        else {
            scroll.setPosition(scroll.getPosition().x, top);
        }
    }

    void Scrollbar::change_total_elements_number(const int new_total_elements_number) {
        total_elements_number = new_total_elements_number;
        if (total_elements_number > visible_elements_number) {
            scroll.setSize(sf::Vector2f(scroll.getSize().x, (static_cast<float>(visible_elements_number)/static_cast<float>(total_elements_number))*height));
        }
        else {
            scroll.setSize(bar.getSize());
        }
    }

    int Scrollbar::get_upper_element_number() const {
        return upper_element_number;
    }

    void Scrollbar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(bar, states);
        target.draw(scroll, states);
    }

    File_List::File_List(const std::string &filename, float pos_x, float pos_y0, float width, float height, float distinction): position_x(pos_x), position_y0(pos_y0), button_width(width), button_height(height), button_distinction(distinction), levels_file(filename), levels_folder(filename.substr(0, filename.size() - 10)) {
        // for (int n = 0; n < 25; n++) {
        //     push_back((Text_Button("THGA" + std::to_string(n), pos_x, pos_y0 + n*distinction, width, height)));
        // }
        int n = 0;
        std::ifstream fout(filename);
        while (!fout.eof()) {
            std::string level_name;
            std::getline(fout, level_name, '\n');
            if (level_name == "\0") {break;}
            push_back(Text_Button(level_name, pos_x, pos_y0 + n*distinction, width, height));
            n++;
        }
        fout.close();
        upper_visible_element_iterator = begin();
        upper_visible_element_number = 1;
    }

    void File_List::change_upper_visible_element(const int change_number) {
//if (total_elements_number > visible_elements_number && new_upper_element_number <= total_elements_number - visible_elements_number + 1 && new_upper_element_number > 0)
//Continuity from class Scrollbar
        if (size() != 0) {
            if (size() < 12) {
                upper_visible_element_number = 1;
                upper_visible_element_iterator = begin();
            }
            else {
                if (change_number <= 0) {
                    upper_visible_element_number = 1;
                    upper_visible_element_iterator = begin();
                }
                else if (change_number > 0 && change_number <= size() - 12 + 1) {
                    int n = 1;
                    for (ListIt it = begin(); it != end(); it++) {
                        if (n == change_number) {upper_visible_element_iterator = it;}
                        it->background.move(0.0f, (upper_visible_element_number - change_number)*50.0f);
                        it->text.move(0.0f, (upper_visible_element_number - change_number)*50.0f);
                        n++;
                    }
                    upper_visible_element_number = change_number;
                }
                else {
                    upper_visible_element_number = size() - 12 + 1;
                    upper_visible_element_iterator = std::prev(end(), 12);
                }
            }
        }
        else {
            upper_visible_element_number = 1;
            upper_visible_element_iterator = begin();
        }
    }

    void File_List::add_level(sf::RenderWindow &window, Scrollbar &scrollbar) {
        static MyFont arial("../pic/text/arial.ttf");
        std::string level_name;
        sf::Text level_text;
        level_text.setFont(arial);
        level_text.setPosition(0.0f, 270.0f);
        sf::Text error_text;
        error_text.setString("This name is already in use or is empty");
        error_text.setFont(arial);
        error_text.setPosition(0.0f, 330.0f);
        error_text.setFillColor(sf::Color::Red);
        bool error_level_name = true;

        while (window.isOpen()) {
            bool escape = false;

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::TextEntered || event.type == sf::Event::KeyPressed) {
                    if (event.type == sf::Event::TextEntered) {
                        sf::Uint32 text = event.text.unicode;
                        if ((text >= '0' && text <= '9') || (text >= 'A' && text <= 'Z') || (text >= 'a' && text <= 'z') || (text == ' ') || (text >= ')' && text <= '.')) {
                            level_name += static_cast<char>(text);
                        }
                    }
                    if (level_name_match(level_name) || const_remove_begin_end_spaces(level_name).empty()) {
                        error_level_name = true;
                    }
                    else {
                        error_level_name = false;
                    }
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Escape) {
                            return;
                        }
                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (!level_name.empty()) {
                                level_name.erase(--level_name.end());
                            }
                        }
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (!level_name.empty() && !error_level_name) {
                                remove_begin_end_spaces(level_name);
                                escape = true;
                            }
                        }
                    }
                }
            }

            if (escape) {break;}
            level_text.setString("Enter text:\n" + level_name);

            window.clear();
            window.draw(level_text);
            if (error_level_name) {
                window.draw(error_text);
            }
            window.display();
        }


        
        if (size() != 0) {
            push_back(Text_Button(level_name, position_x, std::prev(end())->background.getPosition().y + button_distinction, button_width, button_height));
        }
        else {
            push_back(Text_Button(level_name, position_x, position_y0, button_width, button_height));
        }
        change_upper_visible_element(size() - 12 + 1);
        scrollbar.change_total_elements_number(size());
        scrollbar.change_scroll_position(size() - 12 + 1);


        std::ofstream fin_levels(levels_file, std::ios::app);
        fin_levels << level_name + "\n";
        fin_levels.close();

        std::ofstream fin(levels_folder + level_name + ".txt");
        fin << "0.0 0.0\n";
        fin.close();
    }

    void File_List::delete_level(sf::RenderWindow &window, Scrollbar &scrollbar, LevelSelectionCursor &cursor) {
        if (consent_window(window, "Are you sure?")) {
            ListIt mouse_it = cursor.get_mouse_iterator();
            std::string level_name = static_cast<std::string>(mouse_it->text.getString());
            for (ListIt it = std::next(mouse_it); it != end(); it++) {
                it->background.move(0.0f, -button_distinction);
                it->text.move(0.0f, -button_distinction);
            }
            erase(mouse_it);
            change_upper_visible_element(upper_visible_element_number - 1);
            scrollbar.change_total_elements_number(size());
            scrollbar.change_scroll_position(upper_visible_element_number);
            

            std::ofstream fin_levels(levels_file);
            for (ConstListIt it = begin(); it != end(); it++) {
                fin_levels << static_cast<std::string>(it->text.getString()) + "\n";
            }
            fin_levels.close();

            std::remove((levels_folder + level_name + ".txt").c_str());
        }
    }

    File_List::ListIt File_List::mouse_on(const sf::RenderWindow &window) {
        ListIt it = upper_visible_element_iterator;
        for (char i = 0; i < 12; i++) {
            if (it == end()) {break;}
            if (it->background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                return it;
            }
            it++;
        }
        return end();
    }

    int File_List::get_upper_visible_element_number() const {
        return upper_visible_element_number;
    }

    bool File_List::level_name_match(const std::string &level_name) const {
        std::string lvl_name = const_remove_begin_end_spaces(level_name);
        for (ConstListIt it = begin(); it != end(); it++) {
            if (lvl_name == it->text.getString()) {
                return true;
            }
        }
        return false;
    }

    void File_List::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        ConstListIt it = upper_visible_element_iterator;
        for (int i = 0; i < 12; i++) {
            if (it == end()) {break;}
            target.draw((*it), states);
            it++;
        }
    }

    LevelSelectionCursor::LevelSelectionCursor(float pos_x, float pos_y, float width, float height, const sf::Texture &texture, sf::Color color): mouse_on(false), draw_delete_button(false), delete_button(pos_x + width/2.0f - height/2.0f, pos_y, height*0.8f, texture, 2.0f) {
        sprite.setOrigin(width/2.0f, height/2.0f);
        sprite.setSize(sf::Vector2f(width, height));
        sprite.setPosition(pos_x, pos_y);
        sprite.setFillColor(color);
    }

    void LevelSelectionCursor::set_mouse_on(ListIt it, File_List &file_list) {
        if (it != file_list.end()) {
            mouse_on = true;
            sprite.setPosition(sprite.getPosition().x, it->background.getPosition().y);
            delete_button.setPosition(delete_button.getPosition().x, it->background.getPosition().y);
        }
        else {
            mouse_on = false;
        }
        mouse_iterator = it;
    }

    void LevelSelectionCursor::set_draw_delete_button(bool value) {
        draw_delete_button = value;
    }

    LevelSelectionCursor::ListIt LevelSelectionCursor::get_mouse_iterator() const {
        return mouse_iterator;
    }

    void LevelSelectionCursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (mouse_on) {
            target.draw(sprite, states);
            if (draw_delete_button) {
                target.draw(delete_button, states);
            }
        }
    }


}