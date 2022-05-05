#ifndef CITY_MOVEGROUND_HPP
#define CITY_MOVEGROUND_HPP

#include "Background.hpp"


class Moveground : public Background{
public:
    Moveground(float x, float y, std::string string, const RenderWindow &window);

    void horizontal_move(float horizontal_delta, const RenderWindow &window);
};


#endif //CITY_MOVEGROUND_HPP
