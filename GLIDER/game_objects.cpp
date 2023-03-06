#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <utility>

#include "game_objects.hpp"






/////////////////////////////////////////////////////////////////////////
#define COPY_AND_MOVE_CONSTRUCTOR(NAME) \
NAME::NAME(const NAME& value) : sf::RectangleShape(value) {\
    texture = value.texture;\
    setTexture(&texture);\
}\
\
NAME& NAME::operator=(const NAME& value) {\
    (*this).sf::RectangleShape::operator=(value);\
    texture = value.texture;\
    setTexture(&texture);\
    return *this;\
}\
\
NAME::NAME(NAME&& value) : sf::RectangleShape(std::move(value)) {\
    texture = std::move(value.texture);\
    setTexture(&texture);\
}\
\
NAME& NAME::operator=(NAME&& value) {\
    (*this).sf::RectangleShape::operator=(std::move(value));\
    texture = std::move(value.texture);\
    setTexture(&texture);\
    return *this;\
}
/////////////////////////////////////////////////////////////////
#define GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, CLASS, LISTNAME, RECT, RESULT) \
for (std::list<CLASS>::ITER_TYPE it = LISTNAME.begin(), ite = LISTNAME.end(); it != ite; it++) {\
    if (RECT.intersects((*it).getGlobalBounds())) {\
        RESULT\
    }\
}

#define GAME_OBJECTS_SEARCH_FOR_MAP(ITER_TYPE, CLASS, LISTNAME, RECT, RESULT) \
for (std::unordered_multimap<int, CLASS>::ITER_TYPE it = LISTNAME.begin(), ite = LISTNAME.end(); it != ite; it++) {\
    if (RECT.intersects((*it).second.getGlobalBounds())) {\
        RESULT\
    }\
}
/////////////////////////////////////////////////////////////////
#define GAME_OBJECTS_SEARCH_LIST(ITER_TYPE, RECT, RESULT) \
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Background, background_list, RECT, RESULT)\
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Block, block_list, RECT, RESULT)\
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Spike, spike_list, RECT, RESULT)\
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Tramplin, tramplin_list, RECT, RESULT)\
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Shuriken, shuriken_list, RECT, RESULT)\
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Stair, stair_list, RECT, RESULT)\
GAME_OBJECTS_SEARCH_FOR_LIST(ITER_TYPE, Laser, laser_list, RECT, RESULT)
////////////////////////////////////////////////////////////////////
#define GAME_OBJECTS_SEARCH_MAP(ITER_TYPE, RECT, RESULT) \
GAME_OBJECTS_SEARCH_FOR_MAP(ITER_TYPE, Door, door_list, RECT, RESULT) \
GAME_OBJECTS_SEARCH_FOR_MAP(ITER_TYPE, Key, key_list, RECT, RESULT)
/////////////////////////////////////////////////////////////////






namespace krv {

const int factor = 50;

class Colors : public sf::Drawable {
    std::vector<sf::RectangleShape> color_array;
    sf::RectangleShape select;
    bool selected = false;

    void constructor_helper(sf::Color color) {
        sf::RectangleShape shape(sf::Vector2f(700.0f, 40.0f));
        shape.setPosition(50.0f, 40.0f + 80.0f*color_array.size());
        shape.setFillColor(color);
        color_array.push_back(std::move(shape));
    }

  public:
    Colors() {
        constructor_helper(sf::Color::Red);
        constructor_helper(sf::Color(255, 102, 0, 255));
        constructor_helper(sf::Color::Yellow);
        constructor_helper(sf::Color::Green);
        constructor_helper(sf::Color::Blue);
        constructor_helper(sf::Color::Magenta);
        constructor_helper(sf::Color::White);
        select.setFillColor(sf::Color(0, 0, 0, 100));
        select.setSize(sf::Vector2f(700.0f, 40.0f));
    }

    sf::Color update(sf::RenderWindow &window) {
        for (const auto& it : color_array) {
            if (it.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                select.setPosition(it.getPosition());
                selected = true;
                return it.getFillColor();
            }
        }
        selected = false;
        return sf::Color(0, 0, 0, 0);
    }

    bool get_selected() const {
        return selected;
    }

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (const auto& it : color_array) {
            target.draw(it, states);
        }
        if (selected) {
            target.draw(select, states);
        }
    }
};

sf::Color choose_color(sf::RenderWindow &window) {
    sf::View view = window.getView();
    window.setView(window.getDefaultView());
    Colors colors;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (colors.get_selected()) {
                    return colors.update(window);
                }
            }
        }
        colors.update(window);

        window.clear();
        window.draw(colors);
        window.display();
    }
}

bool vertical_direct(const float angle) {
    return ((angle > -45.0f && angle < 45.0f) || (angle > 135.0f && angle < 225.0f));
}

void constructor_template(GAME_OBJECT_TYPE type, sf::RectangleShape &value, sf::Texture &texture, const sf::FloatRect &floatrect, const float angle = 0.0f) {
    value.setPosition(floatrect.left, floatrect.top);
    value.setSize(sf::Vector2f(floatrect.width, floatrect.height));

    sf::RenderTexture render_texture;
    int x = static_cast<int>(floatrect.width);
    int y = static_cast<int>(floatrect.height);
    render_texture.create(factor*x, factor*y);
    render_texture.clear(sf::Color(255, 255, 255, 0));
    sf::RectangleShape shape(sf::Vector2f(factor, factor));
    sf::Texture buffer;
    buffer.loadFromFile("../pic/game_objects.png");
    shape.setTexture(&buffer);
    shape.setTextureRect(sf::IntRect(static_cast<int>(type)*factor, 0, factor, factor));
    shape.rotate(angle);
    shape.setOrigin(shape.getSize()/2.0f);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            shape.setPosition(factor*i + factor/2.0f, factor*j + factor/2.0f);
            render_texture.draw(shape);
        }
    }
    render_texture.display();
    texture = render_texture.getTexture();
    value.setTexture(&texture);
}

void half_constructor_template(GAME_OBJECT_TYPE type, sf::RectangleShape &value, sf::Texture &texture, const sf::FloatRect &floatrect, const float angle = 0.0f) {
    value.setPosition(floatrect.left, floatrect.top);
    value.setSize(sf::Vector2f(floatrect.width, floatrect.height));

    sf::RenderTexture render_texture;
    int x = static_cast<int>(floatrect.width);
    int y = static_cast<int>(floatrect.height);
    render_texture.create(factor*x, factor*y);
    render_texture.clear(sf::Color(255, 255, 255, 0));
    sf::RectangleShape shape(sf::Vector2f(factor, factor/2.0f));
    sf::Texture buffer;
    buffer.loadFromFile("../pic/game_objects.png");
    shape.setTexture(&buffer);
    shape.setOrigin(shape.getSize()/2.0f);

    //rotate texture
    if (!vertical_direct(angle)) {
        std::swap(x, y);
        sf::View view(render_texture.getDefaultView());
        view.setRotation(angle);
        view.setCenter(view.getCenter().y, view.getCenter().x);
        render_texture.setView(view);
    }

    //draw between
    shape.setTextureRect(sf::IntRect(static_cast<int>(type)*factor, 0, factor, factor/2.0f));
    for (int i = 0; i < x; i++) {
        for (int j = 1; j < (2*y - 1); j++) {
            shape.setPosition(factor*i + factor/2.0f, factor*j/2.0f + factor/4.0f);
            render_texture.draw(shape);
        }
    }
    //draw deeper part
    shape.setTextureRect(sf::IntRect(static_cast<int>(type)*factor, factor/2.0f, factor, factor/2.0f));
    for (int i = 0; i < x; i++) {
        shape.setPosition(factor*i + factor/2.0f, factor*(2*y - 1)/2.0f + factor/4.0f);
        render_texture.draw(shape);
    }
    //draw upper part
    shape.rotate(180);
    shape.setTextureRect(sf::IntRect(static_cast<int>(type)*factor, factor/2.0f, factor, factor/2.0f));
    for (int i = 0; i < x; i++) {
        shape.setPosition(factor*i + factor/2.0f, factor/4.0f);
        render_texture.draw(shape);
    }

    render_texture.display();
    texture = render_texture.getTexture();
    value.setTexture(&texture);
}





Block::Block(const sf::FloatRect &floatrect) : sf::RectangleShape() {
    constructor_template(GAME_OBJECT_TYPE::BLOCK, (*this), texture, floatrect);
}

COPY_AND_MOVE_CONSTRUCTOR(Block)




Spike::Spike(const sf::FloatRect &floatrect, const float angle) {
    constructor_template(GAME_OBJECT_TYPE::SPIKE, (*this), texture, floatrect, angle);
}

COPY_AND_MOVE_CONSTRUCTOR(Spike)



Tramplin::Tramplin(const sf::FloatRect &floatrect) {
    constructor_template(GAME_OBJECT_TYPE::TRAMPLIN, (*this), texture, floatrect);
}

COPY_AND_MOVE_CONSTRUCTOR(Tramplin)



Shuriken::Shuriken(const sf::FloatRect &floatrect) {
    float size_x = floatrect.width, size_y = floatrect.height;
    if (size_x < size_y) {size_y = size_x;}
    else {size_x = size_y;}
    setSize(sf::Vector2f(size_x, size_x));
    setOrigin(getSize()/2.0f);
    setPosition(sf::Vector2f(floatrect.left, floatrect.top) + getOrigin());
    texture.loadFromFile("../pic/shuriken.png");
    setTexture(&texture);
}

COPY_AND_MOVE_CONSTRUCTOR(Shuriken)



Stair::Stair(const sf::FloatRect &floatrect, const float angle) {
    half_constructor_template(GAME_OBJECT_TYPE::STAIR, (*this), texture, floatrect, angle);
}

COPY_AND_MOVE_CONSTRUCTOR(Stair)



sf::Shader Laser::shader;

Laser::Laser(const sf::FloatRect &floatrect, const float angle) {
    //TODO: Time, period
    half_constructor_template(GAME_OBJECT_TYPE::LASER, (*this), texture, floatrect, angle);
}

Laser::Laser(const Laser& value) : sf::RectangleShape(value) {
    t_down = value.t_down;
    t_up = value.t_up;
    t0 = value.t0;
    texture = value.texture;
    setTexture(&texture);
}

Laser& Laser::operator=(const Laser& value) {
    (*this).sf::RectangleShape::operator=(value);
    t_down = value.t_down;
    t_up = value.t_up;
    t0 = value.t0;
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Laser::Laser(Laser&& value) : sf::RectangleShape(std::move(value)) {
    t_down = value.t_down;
    t_up = value.t_up;
    t0 = value.t0;
    texture = std::move(value.texture);
    setTexture(&texture);
}

Laser& Laser::operator=(Laser&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    t_down = value.t_down;
    t_up = value.t_up;
    t0 = value.t0;
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}

void Laser::set_shader() {
    shader.loadFromFile("../shaders/laser.frag", sf::Shader::Fragment);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!is_work) {
        states.shader = &shader;
    }
    target.draw(static_cast<sf::RectangleShape>(*this), states);
}



Door::Door(const sf::FloatRect &floatrect, sf::RenderWindow &window) {
    constructor_template(GAME_OBJECT_TYPE::DOOR, (*this), texture, floatrect);
    setFillColor(choose_color(window));
}

COPY_AND_MOVE_CONSTRUCTOR(Door)



Key::Key(const sf::FloatRect &floatrect, sf::RenderWindow &window) {
    constructor_template(GAME_OBJECT_TYPE::KEY, (*this), texture, floatrect);
    setFillColor(choose_color(window));
}

COPY_AND_MOVE_CONSTRUCTOR(Key)



Finish::Finish(const sf::FloatRect &floatrect) {
    setPosition(floatrect.left, floatrect.top);
    setSize(sf::Vector2f(1.0f, 1.0f));
    texture.loadFromFile("../pic/game_objects.png", sf::IntRect(static_cast<int>(GAME_OBJECT_TYPE::FINISH)*factor, 0, factor, factor));
    setTexture(&texture);
}

COPY_AND_MOVE_CONSTRUCTOR(Finish)



Background::Background(const sf::FloatRect &floatrect) {
    constructor_template(GAME_OBJECT_TYPE::BACKGROUND, (*this), texture, floatrect);
}

COPY_AND_MOVE_CONSTRUCTOR(Background)





void Game_Objects::add(sf::RenderWindow &window, GAME_OBJECT_TYPE type, const sf::FloatRect &floatrect, const float angle) {
    if (floatrect.height < build_cursor_size_red && floatrect.width < build_cursor_size_red) {
        if (!intersects(floatrect) && !floatrect.intersects(sf::FloatRect(-0.5f, -0.5f, 1.0f, 1.0f))) {
            switch (type) {
                case GAME_OBJECT_TYPE::BLOCK: {
                    block_list.push_front(Block(floatrect));
                    break;
                }
                case GAME_OBJECT_TYPE::SPIKE: {
                    spike_list.push_front(Spike(floatrect, angle));
                    break;
                }
                case GAME_OBJECT_TYPE::TRAMPLIN: {
                    tramplin_list.push_front(Tramplin(floatrect));
                    break;
                }
                case GAME_OBJECT_TYPE::STAIR: {
                    stair_list.push_front(Stair(floatrect, angle));
                    break;
                }
                case GAME_OBJECT_TYPE::LASER: {
                    laser_list.push_front(Laser(floatrect, angle));
                    break;
                }
                case GAME_OBJECT_TYPE::DOOR: {
                    Door door(floatrect, window);
                    door_list.insert(std::make_pair(door.getFillColor().toInteger(), std::move(door)));
                    break;
                }
                case GAME_OBJECT_TYPE::KEY: {
                    Key key(floatrect, window);
                    key_list.insert(std::make_pair(key.getFillColor().toInteger(), std::move(key)));
                    break;
                }
                case GAME_OBJECT_TYPE::FINISH: {
                    finish = Finish(floatrect);
                    break;
                }
            }
        }
        if (type == GAME_OBJECT_TYPE::SHURIKEN) {
            shuriken_list.push_front(Shuriken(floatrect));
        }
        if (type == GAME_OBJECT_TYPE::BACKGROUND) {
            if (!intersects_for_background(floatrect)) {
                background_list.push_front(Background(floatrect));
            }
        }
    }
}

void Game_Objects::remove(const sf::FloatRect &floatrect) {
    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Block, block_list, floatrect, block_list.erase(it); return;)
    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Spike, spike_list, floatrect, spike_list.erase(it); return;)
    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Tramplin, tramplin_list, floatrect, tramplin_list.erase(it); return;)
    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Stair, stair_list, floatrect, stair_list.erase(it); return;)
    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Laser, laser_list, floatrect, laser_list.erase(it); return;)

    GAME_OBJECTS_SEARCH_FOR_MAP(iterator, Door, door_list, floatrect, door_list.erase(it); return;)
    GAME_OBJECTS_SEARCH_FOR_MAP(iterator, Key, key_list, floatrect, key_list.erase(it); return;)

    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Shuriken, shuriken_list, floatrect, shuriken_list.erase(it); return;)
    GAME_OBJECTS_SEARCH_FOR_LIST(iterator, Background, background_list, floatrect, background_list.erase(it); return;)
}

bool Game_Objects::intersects(const sf::FloatRect &floatrect) const {
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Block, block_list, floatrect, return true;)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Spike, spike_list, floatrect, return true;)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Tramplin, tramplin_list, floatrect, return true;)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Stair, stair_list, floatrect, return true;)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Laser, laser_list, floatrect, return true;)
    GAME_OBJECTS_SEARCH_MAP(const_iterator, floatrect, return true;)
    if (floatrect.intersects(finish.getGlobalBounds())) {
        return true;
    }
    return false;
}

bool Game_Objects::intersects_for_background(const sf::FloatRect &floatrect) const {
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Background, background_list, floatrect, return true;)
    return false;
}

void Game_Objects::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::FloatRect rect = sf::FloatRect(target.getView().getCenter() - target.getView().getSize()/2.0f, target.getView().getSize());
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Background, background_list, rect, target.draw((*it), states);)
    target.draw(player, states);
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Shuriken, shuriken_list, rect, target.draw((*it), states);)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Block, block_list, rect, target.draw((*it), states);)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Spike, spike_list, rect, target.draw((*it), states);)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Tramplin, tramplin_list, rect, target.draw((*it), states);)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Stair, stair_list, rect, target.draw((*it), states);)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Laser, laser_list, rect, target.draw((*it), states);)
    GAME_OBJECTS_SEARCH_MAP(const_iterator, rect, target.draw(it->second, states);)
    if (rect.intersects(finish.getGlobalBounds())) {
        target.draw(finish, states);
    }
}

sf::FloatRect Game_Objects::remove_shading(const sf::FloatRect &floatrect) const {
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Block, block_list, floatrect, return it->getGlobalBounds();)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Spike, spike_list, floatrect, return it->getGlobalBounds();)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Tramplin, tramplin_list, floatrect, return it->getGlobalBounds();)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Stair, stair_list, floatrect, return it->getGlobalBounds();)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Laser, laser_list, floatrect, return it->getGlobalBounds();)

    GAME_OBJECTS_SEARCH_MAP(const_iterator, floatrect, return it->second.getGlobalBounds();)

    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Shuriken, shuriken_list, floatrect, return it->getGlobalBounds();)
    GAME_OBJECTS_SEARCH_FOR_LIST(const_iterator, Background, background_list, floatrect, return it->getGlobalBounds();)

    return sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
}

Game_Objects::Game_Objects() {
    Laser::set_shader();
}


}