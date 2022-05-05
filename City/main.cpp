#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>


bool exit_game = false;
const float horizontal_speed = 100.0f;
float game_time = 0.0f;
const float player_start_x = 150.0f;
const int noc = 5;
bool end_game = false;

#include "Button.hpp"
#include "Moveground.hpp"
#include "Player.hpp"
#include "Column.hpp"

using namespace sf;

void game_window();
void main_menu(RenderWindow &window);
void game_screen(RenderWindow &window);
void game_cycle(RenderWindow &window, Moveground &terrain, Player &player, Column *column, Moveground &sky);
void columns_planting(Column *column);
void columns_draw(RenderWindow &window, Column *column);
void player_columns_collision(Player &player, Column *column);

int main() {

    FreeConsole();

    srand(time(nullptr));

    game_window();

    return 0;
}

void game_window() {
    RenderWindow window(VideoMode(480, 800), "Flappy Bird", Style::Close);
    window.setFramerateLimit(144);

    main_menu(window);
}

void main_menu(RenderWindow &window) {
    Background background(window, "../pic/menu_background.png");
    Button play_button(120, 625, 200, 100, "../pic/play_button.png");
    Button exit_button(360, 625, 200, 100, "../pic/exit_button.png");

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed || exit_button.smth_pressed_on(Mouse::getPosition(window).x, Mouse::getPosition(window).y, event) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                window.close();
                return;
            }
            if (play_button.smth_pressed_on(Mouse::getPosition(window).x, Mouse::getPosition(window).y, event) || event.type == Event::KeyPressed) {
                while(true) {
                    game_screen(window);
                    if (exit_game) {
                        exit_game = false;
                        break;
                    }
                }
            }

        }

        window.clear();
        window.draw(background.sprite);
        if (play_button.point_on(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
            play_button.sprite.setFillColor(Color(200,200,200,255));
        }
        else {
            play_button.sprite.setFillColor(Color::White);
        }
        if (exit_button.point_on(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
            exit_button.sprite.setFillColor(Color(200,200,200,255));
        }
        else {
            exit_button.sprite.setFillColor(Color::White);
        }
        window.draw(play_button.sprite);
        window.draw(exit_button.sprite);
        window.display();
    }
}

void game_screen(RenderWindow &window) {
    end_game = false;
    Font font;
    font.loadFromFile("../pic/text/Carno.otf");
    Text board;
    board.setFont(font);
    board.setCharacterSize(90);
    Background background(window, "../pic/background.png");
    Moveground terrain(2.0f * window.getSize().x, (13.0f / 80.0f) * window.getSize().y, "../pic/terrain.png", window);
    Moveground sky(2.0f * window.getSize().x, window.getSize().y, "../pic/sky.png", window);
    Player player(player_start_x, 400.0f);
    Column column[noc];
    columns_planting(column);
    Clock clock;

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
                exit_game = true;
                return;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                exit_game = true;
                return;
            }

            if (event.type == Event::MouseButtonPressed || event.type == Event::KeyPressed) {
                player.player_change_speed();
            }

        }

        window.clear();
        game_time = static_cast<float>(clock.getElapsedTime().asMicroseconds())/1000000.0f;
        clock.restart();
        game_cycle(window, terrain, player, column, sky);
        window.draw(background.sprite);
        window.draw(sky.sprite);
        window.draw(terrain.sprite);
        columns_draw(window, column);
        window.draw(player.sprite);
        board.setString(std::to_string( static_cast<int>((player.score + player_start_x - lenght_beetwin_columns - player.sprite.getOrigin().x - column_width)/lenght_beetwin_columns) ));
        board.setPosition(0.0f, -board.getLocalBounds().height/2.7f);
        window.draw(board);
        window.display();
        if (end_game) {
            Sleep(250);
            return;
        }
    }
}

void game_cycle(RenderWindow &window, Moveground &terrain, Player &player, Column *column, Moveground &sky) {
    player_columns_collision(player, column);
    if (end_game) {return;}
    terrain.horizontal_move(horizontal_speed*game_time, window);
    sky.horizontal_move(horizontal_speed*game_time/2.0f, window);
    player.player_game_cycle(window, game_time);
    for (int i = 0; i < noc; i++) {
        column[i].column_game_cycle(horizontal_speed*game_time);
    }
    player.score += horizontal_speed*game_time;
}

void player_columns_collision(Player &player, Column *column) {
    for (int i = 0; i < noc; i++) {
        if (player.sprite.getGlobalBounds().intersects(column[i].upper.getGlobalBounds())) {
            end_game = true;
        }
        if (player.sprite.getGlobalBounds().intersects(column[i].lower.getGlobalBounds())) {
            end_game = true;
        }
    }
}

void columns_planting(Column *column) {
    for (int i = 0; i < noc; i++) {
        column[i].ColumnCtr( (i+2)*lenght_beetwin_columns, rand()%(600 - (int)gap_length) + 100);
    }
}

void columns_draw(RenderWindow &window, Column *column) {
    for (int i = 0; i < noc; i++) {
        window.draw(column[i].upper);
        window.draw(column[i].lower);
    }
}