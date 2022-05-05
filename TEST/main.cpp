#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>

#include "Player.hpp"
#include "Tile.hpp"
#include "Background.hpp"
#include "Button.hpp"

using namespace sf;

bool game_screen(RenderWindow &window);
void game_menu(const VideoMode &resolution);
bool game_cycle(RenderWindow &window, Player &player, Tile *tile, float time);
void player_horizontal_move(RenderWindow &window, Player &player, float time);
void player_vertical_move(Player &player, float time);
void player_tile_collision(RenderWindow &window, Player &player, Tile *tile, float time);
void tile_horizontal_move(RenderWindow &window, Tile *tile, float time);
void tile_changing(RenderWindow &window, Tile *tile, float const_delta, float rand_delta, Tile_Type type_setting = Tile_Type::NONE);
void functions_for_ROOF_type_tile_other_cases(Player &player, Tile *tile, float time);
void tile_planting(RenderWindow &window, Tile *tile, float const_delta, float rand_delta, Tile_Type type_setting = Tile_Type::NONE);
void tile_setting(RenderWindow &window, Tile *tile, float delta, int i, Tile_Type type_setting = Tile_Type::NONE);
void player_check_out_window_horizontal(Player &player, RenderWindow &window);
void tile_making(RenderWindow &window, Player &player, Tile *tile, float const_delta, float rand_delta);
void board_update(Text &board, Player &player);
void button_update(Button &button, RenderWindow &window);

int main() {

    FreeConsole();

    srand(time(nullptr));

    game_menu(VideoMode(480, 800));

    return 0;
}

void game_menu(const VideoMode &resolution) {

  RenderWindow window(resolution, "JUMPER", Style::Close);
  window.setFramerateLimit(144);
  Background background( static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), "../pic/menu_background.png" );
  Button button_play(window.getSize().x/4.0f, 0.75f*window.getSize().y, 0.375f*window.getSize().x, 0.125f*window.getSize().y, "../pic/playbutton.png");
  Button button_exit(0.75f*window.getSize().x, 0.75f*window.getSize().y, 0.375f*window.getSize().x, 0.125f*window.getSize().y, "../pic/exitbutton.png");
  Button button_reset(0.93f*window.getSize().x, 0.93*window.getSize().y, 0.05f*window.getSize().y, 0.05f*window.getSize().y, "../pic/resetbutton.png");


  while (window.isOpen()) {

    Event event;
    while (window.pollEvent(event)) {

      if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) ) {
        window.close();
        return;
      }
      if (button_play.smth_pressed_on( static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), event)) {
        while (game_screen(window)) {}
      }
      if (button_reset.smth_pressed_on(Mouse::getPosition(window).x, Mouse::getPosition(window).y, event)) {
        Player::player_best_score_recording(0.0f);
      }
      if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
        while (game_screen(window)) {}
      }
      if (button_exit.smth_pressed_on( static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y), event)) {
        window.close();
        return;
      }

    }

    button_update(button_exit, window);
    button_update(button_play, window);
    button_update(button_reset, window);

    window.clear();
    window.draw(background.sprite);
    window.draw(button_play.sprite);
    window.draw(button_exit.sprite);
    window.draw(button_reset.sprite);
    window.display();

  }

}

bool game_screen(RenderWindow &window) {

  Clock clock;
  Background background( static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) , "../pic/game_background.png");
  Player player;
  Tile tile[10];
  Font arial;
  arial.loadFromFile("../pic/text/Carno.otf");
  Text board( String(std::to_string(static_cast<long long>(player.score))), arial, 30);
  tile_planting(window, tile, const_delta_between_tiles, rand_delta_between_tiles, Tile_Type::SIMPLE);

  while (window.isOpen()) {

    Event event;
    while (window.pollEvent(event)) {

      if (event.type == Event::Closed) {
        window.close();
      }
      if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        return false;
      }

    }



    window.clear();
    float time = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / 1000000.0f;
    clock.restart();
    if (!game_cycle(window, player, tile, time)) {
      return true;
    }
    window.draw(background.sprite);
    for (int i = 0; i < 10; i++) {
      window.draw(tile[i].sprite);
    }
    window.draw(player.sprite);
    board_update(board, player);
    window.draw(board);
    window.display();

  }
  return false;
}

bool game_cycle(RenderWindow &window, Player &player, Tile *tile, float time) {


  player_horizontal_move(window, player, time);
  player_vertical_move(player, time);
  tile_horizontal_move(window, tile, time);

  //Processing event when player above//
  if (player.sprite.getPosition().y < max_height) {
    float delta = max_height - player.sprite.getPosition().y;
    player.sprite.move( Vector2f(0.0f, delta) );
    player.score = player.score + delta/20.0f;
    for (int i = 0; i < 10; i++) {
      tile[i].sprite.move( Vector2f(0.0f, delta) );
    }
  }

  player_check_out_window_horizontal(player, window);

  player_tile_collision(window, player, tile, time);


  //Processing tile events and creating new tiles////
  tile_making(window, player, tile, const_delta_between_tiles, rand_delta_between_tiles);

  //End Game//
  if (player.sprite.getGlobalBounds().top > 1.5f*static_cast<float>(window.getSize().y) ) {
    return false;
  }

  return true;

}

void tile_making(RenderWindow &window, Player &player, Tile *tile, float const_delta, float rand_delta) {
  static Tile_Type tile_type_changing = Tile_Type::NONE;
  if ( static_cast<int>(player.score)%score_between_events < score_length_events && player.score >= score_between_events ) {
    if (tile_type_changing == Tile_Type::NONE) {
      int var = rand()%(number_of_tile_types() - 2);
      tile_type_changing = static_cast<Tile_Type>(var);
    }
  }
  else {
    if (tile_type_changing != Tile_Type::NONE) {
      tile_type_changing = Tile_Type::NONE;
    }
  }
  tile_changing(window, tile, const_delta, rand_delta, tile_type_changing);
}

void tile_changing(RenderWindow &window, Tile *tile, float const_delta, float rand_delta, Tile_Type type_setting) {
  for (int i = 0; i < 10; i++) {
    if (tile[i].sprite.getGlobalBounds().top > static_cast<float>(window.getSize().y) ) {
      float delta;
      if (i == 0) {
        delta = tile[9].sprite.getPosition().y - const_delta - static_cast<float>( rand() % static_cast<int>(rand_delta) );
      }
      else {
        delta = tile[i-1].sprite.getPosition().y - const_delta - static_cast<float>( rand() % static_cast<int>(rand_delta) );
      }

      tile_setting(window, tile, delta, i, type_setting);
      tile[i].speed_generator();
    }
  }
}

void tile_planting(RenderWindow &window, Tile *tile, float const_delta, float rand_delta, Tile_Type type_setting) {
  for (int i = 0; i < 10; i++) {
    float delta;
    if (i == 0) {
      delta = height_first_tile;
    }
    else {
      delta = tile[i-1].sprite.getPosition().y - const_delta - static_cast<float>( rand() % static_cast<int>(rand_delta) );
    }

    tile_setting(window, tile, delta, i, type_setting);
    tile[i].speed_generator();
  }
}

void tile_setting(RenderWindow &window, Tile *tile, float delta, int i, Tile_Type type_setting) {
  if (type_setting != Tile_Type::NONE) {
    tile[i].TileSet(static_cast<float>( rand()%(window.getSize().x) ), delta, type_setting);
    return;
  }

  int var = rand()%1000;
  if (var <= 999 && var >=997) {
    tile[i].TileSet( static_cast<float>( rand()%(window.getSize().x) ), delta, Tile_Type::TELEPORT);
  }
  if (var <= 996 && var >=940) {
    tile[i].TileSet( static_cast<float>( rand()%(window.getSize().x) ), delta, Tile_Type::ROOF);
  }
  if (var <= 939 && var >= 860) {
    tile[i].TileSet( static_cast<float>( rand()%(window.getSize().x) ), delta, Tile_Type::JUMP);
  }
  if (var <= 859 && var >= 800) {
    tile[i].TileSet( static_cast<float>( rand()%(window.getSize().x) ), delta, Tile_Type::HIDER);
  }
  if (var <= 799 && var >= 0) {
    tile[i].TileSet( static_cast<float>( rand()%(window.getSize().x) ), delta, Tile_Type::SIMPLE);
  }
}

void tile_horizontal_move(RenderWindow &window, Tile *tile, float time) {
  for (int i = 0; i < 10; i++) {
    if (tile[i].get_speed() != 0.0f) {
      tile[i].sprite.move( Vector2f( tile[i].get_speed()*time, 0.0f) );
    }
    if (tile[i].sprite.getGlobalBounds().left < 0.0f) {
      tile[i].sprite.move( Vector2f( -tile[i].sprite.getGlobalBounds().left, 0.0f) );
      tile[i].change_speed();
    }
    if (tile[i].sprite.getGlobalBounds().left + tile[i].sprite.getGlobalBounds().width > static_cast<float>(window.getSize().x)) {
      tile[i].sprite.move( Vector2f( -( tile[i].sprite.getGlobalBounds().left + tile[i].sprite.getGlobalBounds().width - static_cast<float>(window.getSize().x)), 0.0f) );
      tile[i].change_speed();
    }
  }
}

void player_tile_collision(RenderWindow &window, Player &player, Tile *tile, float time) {
  if (player.speed < 0.0f) {
    for (int i = 0; i < 10; i++) {
      if (tile[i].sprite.getGlobalBounds().intersects( FloatRect( player.sprite.getGlobalBounds().left, player.sprite.getPosition().y - tile[i].sprite.getSize().y/2.0f, player.sprite.getSize().x, tile[i].sprite.getSize().y/2.0f) )) {
        switch (tile[i].get_type()) {
          case Tile_Type::SIMPLE: {
            player.sprite.setPosition(Vector2f(player.sprite.getPosition().x, tile[i].sprite.getGlobalBounds().top));
            player.speed = push_vertical_V;
            break;
          }
          case Tile_Type::JUMP: {
            player.sprite.setPosition(Vector2f(player.sprite.getPosition().x, tile[i].sprite.getGlobalBounds().top));
            player.speed = 1.5f * push_vertical_V;
            break;
          }
          case Tile_Type::TELEPORT: {
            player.sprite.setPosition(Vector2f(player.sprite.getPosition().x, tile[i].sprite.getGlobalBounds().top));
            player.speed = push_vertical_V;
            tile_planting(window, tile, const_delta_between_tiles, rand_delta_between_tiles, Tile_Type::SIMPLE);
            break;
          }
          case Tile_Type::ROOF: {
            player.sprite.setPosition(Vector2f(player.sprite.getPosition().x, tile[i].sprite.getGlobalBounds().top));
            player.speed = push_vertical_V;
            break;
          }
          case Tile_Type::HIDER: {
            player.sprite.setPosition(Vector2f(player.sprite.getPosition().x, tile[i].sprite.getGlobalBounds().top));
            player.speed = push_vertical_V;
            tile[i].TileSet(tile[i].get_pos().x, tile[i].get_pos().y, Tile_Type::NONE);
            break;
          }
          case Tile_Type::NONE: {
            break;
          }
          //TODO:default case
        }
      }
    }
  }
  functions_for_ROOF_type_tile_other_cases(player, tile, time);
}

void functions_for_ROOF_type_tile_other_cases(Player &player, Tile *tile, float time) {
  for (int i = 0; i < 10; i++) {
    if (tile[i].get_type() == Tile_Type::ROOF && tile[i].sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
      ///////If touch from down////////
      if (player.sprite.getGlobalBounds().top < tile[i].sprite.getGlobalBounds().top + tile[i].sprite.getGlobalBounds().height && player.sprite.getGlobalBounds().top + (player.speed + 2*G*time)*time > tile[i].sprite.getGlobalBounds().top + tile[i].sprite.getGlobalBounds().height) {
        player.sprite.move(0.0f, -player.sprite.getGlobalBounds().top + tile[i].sprite.getGlobalBounds().top + tile[i].sprite.getGlobalBounds().height);
        if (player.speed > 0.0f) {
          player.speed = -player.speed;
        }
      }
        ///////If touch from left////////
      else if (player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width > tile[i].sprite.getGlobalBounds().left && player.sprite.getGlobalBounds().left < tile[i].sprite.getGlobalBounds().left) {
        player.sprite.move( tile[i].sprite.getGlobalBounds().left - player.sprite.getGlobalBounds().left - player.sprite.getGlobalBounds().width, 0.0f);
      }
        ///////If touch from right////////
      else if (player.sprite.getGlobalBounds().left < tile[i].sprite.getGlobalBounds().left + tile[i].sprite.getGlobalBounds().width && player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width > tile[i].sprite.getGlobalBounds().left + tile[i].sprite.getGlobalBounds().width) {
        player.sprite.move( tile[i].sprite.getGlobalBounds().left + tile[i].sprite.getGlobalBounds().width - player.sprite.getGlobalBounds().left, 0.0f);
      }
    }
  }
}

void player_vertical_move(Player &player, float time) {
  player.sprite.move(Vector2f(0.0f, -player.speed * time));
  player.speed = player.speed - G * time;
  if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
    player.speed = player.speed - G * time;
  }
}

void player_horizontal_move(RenderWindow &window, Player &player, float time) {
  if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
    player.sprite.move(Vector2f(horizontal_V * time, 0.0f));
  }
  if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
    player.sprite.move(Vector2f(-horizontal_V * time, 0.0f));
  }
}

void player_check_out_window_horizontal(Player &player, RenderWindow &window) {
  if (player.sprite.getGlobalBounds().left < 0.0f) {
    player.sprite.move(-player.sprite.getGlobalBounds().left, 0.0f);
  }
  if (player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width > window.getSize().x) {
    player.sprite.move( window.getSize().x - (player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width), 0.0f);
  }
}

void board_update(Text &board, Player &player) {
  if (player.score > player.best_score) {
    player.best_score = player.score;
  }
  if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
    board.setString(String(std::to_string(static_cast<long long>(player.score))) + "\n" + "Best Score: " + String(std::to_string(static_cast<long long>(player.best_score))));
    return;
  }
  board.setString(String(std::to_string(static_cast<long long>(player.score))));
}

void button_update(Button &button, RenderWindow &window) {
  if (button.point_on(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
    button.sprite.setFillColor(Color(200,200,200,255));
  }
  else {
    button.sprite.setFillColor(Color::White);
  }
}