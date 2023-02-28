#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>


namespace krv{

bool consent_window(sf::RenderWindow &window);





class Quadratic_Button : public sf::RectangleShape {
    float n; // (x-x0)^n + (y-y0)^n < r^n

  public:
    Quadratic_Button(const float pos_x, const float pos_y, const float length, const float n = NAN);

    Quadratic_Button(const float pos_x, const float pos_y, const float length, const sf::Texture &texture, const float n = NAN);

    bool mouse_on(const sf::RenderWindow &window) const;

    void shading(const sf::RenderWindow &window);
};




class LevelSelectionCursor;





class Text_Button : public sf::Drawable {
  private:
    const std::string path;
  public:
    sf::Text text;
    sf::RectangleShape background;


    enum class ALIGNMENT_TYPE {
        LEFT,
        CENTER,
        RIGHT, //experimental
    };



    Text_Button(const std::string &text_string, const float pos_x, const float pos_y, const float width, const float height, const ALIGNMENT_TYPE alignment_type = ALIGNMENT_TYPE::LEFT, const sf::Color color = sf::Color(147, 147, 147, 255));


  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};









class Scrollbar : public sf::Drawable { //Use if you see integer number of visible elements
  private:
    int total_elements_number;
    int visible_elements_number;
    int upper_element_number;
    const float top;
    const float height;
  public:
    sf::RectangleShape bar;
    sf::RectangleShape scroll;


    Scrollbar(const int total_elements_number, const int visible_elements_number, const float pos_x, const float pos_y, const float width, const float height, const sf::Color bar_color = sf::Color(128, 128, 128, 255), const sf::Color scroll_color = sf::Color(192, 192, 192, 255));


    void change_scroll_position(const int new_upper_element_number);

    void change_total_elements_number(const int new_total_elements_number);

    int get_upper_element_number() const;


  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};











//If other classes are made for the general case, then this one is designed for only one task
class File_List : public sf::Drawable, public std::list<Text_Button> {
    using ListIt = typename File_List::iterator;
    using ConstListIt = typename File_List::const_iterator;
    
    float position_x;
    float position_y0;
    float button_width;
    float button_height;
    float button_distinction;
    ListIt upper_visible_element_iterator;
    int upper_visible_element_number;

  public:
    const std::string levels_file;
    const std::string levels_folder;


    File_List(const std::string &filename, float pos_x, float pos_y0, float width, float height, float distinction);
    

    void change_upper_visible_element(const int change_number);

    void add_level(sf::RenderWindow &window, Scrollbar &scrollbar);

    void delete_level(sf::RenderWindow &window, Scrollbar &scrollbar, LevelSelectionCursor &cursor);

    ListIt mouse_on(const sf::RenderWindow &window);

    int get_upper_visible_element_number() const;

    bool level_name_match(const std::string &level_name) const;

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};














class LevelSelectionCursor : public sf::Drawable {
    using ListIt = typename File_List::iterator;
    bool mouse_on;
    bool draw_delete_button;
    ListIt mouse_iterator;
  public:
    Quadratic_Button delete_button;
    sf::RectangleShape sprite;

    
    LevelSelectionCursor(float pos_x, float pos_y, float width, float height, const sf::Texture &texture, sf::Color color = sf::Color(255, 255, 255, 75));

    void set_mouse_on(ListIt it, File_List &file_list);

    void set_draw_delete_button(bool value);

    ListIt get_mouse_iterator() const;

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};




}