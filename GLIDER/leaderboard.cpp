#include <fstream>
#include <string>
#include <iostream>
#include "leaderboard.hpp"

namespace krv {

    const int number_of_leaders = 10;

    LeaderBoard::LeaderBoard(const std::string &filename) : filename(filename) {
        arial.loadFromFile("../pic/text/arial.ttf");
        scores_table.setFont(arial);
        leaders_table.setFont(arial);
        leaders_table.setPosition(0.0f, 100.0f);
        scores_table.setPosition(400.0f, 100.0f);
        background.setFillColor(sf::Color(100, 100, 100, 100));
        background.setSize(sf::Vector2f(800.0f, 600.0f));

        load();

        print_scores();
    }

    void LeaderBoard::print_scores() {
        std::string str;
        for (const auto& buff : leader_board) {
            str += (buff.first + "\n");
        }
        leaders_table.setString(str);
        str.clear();

        for (const auto& buff : leader_board) {
            str += (std::to_string(buff.second / 1000) + "." + (std::to_string(buff.second % 1000)) + "\n");
        }
        scores_table.setString(str);
    }

    void LeaderBoard::load() {
        std::ifstream fout(filename);
        while (!fout.eof()) {
            std::string buff;
            fout >> buff;
            if (fout.eof()) {
                break;
            }
            unsigned long long score;
            fout >> score;
            leader_board.push_back(std::make_pair(buff, score));
        }
        fout.close();
    }

    void LeaderBoard::save(sf::RenderWindow &window, long long time) {
        if (leader_board.size() < number_of_leaders || time < leader_board[leader_board.size() - 1].second) {
            bool escape = false;
            sf::Text text;
            text.setFont(arial);
            text.setString("This is time for leaderboard!\nEnter your name:");

            leader_board.emplace_back(":", time);
            std::sort(leader_board.begin(), leader_board.end(), [](const std::pair<std::string, unsigned long long> &left, const std::pair<std::string, unsigned long long> &right) -> bool {
                return left.second < right.second;
            });
            if (leader_board.size() > number_of_leaders) {
                leader_board.erase(std::prev(leader_board.end()));
            }

            int n;
            for (int i = 0, size = leader_board.size(); i < size; i++) {
                if (leader_board[i].first == ":") {
                    n = i;
                    break;
                }
            }
            std::string& name = leader_board[n].first;
            print_scores();



            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                    if (event.type == sf::Event::TextEntered) {
                        if (name.size() <= 21) {
                            sf::Uint32 character = event.text.unicode;
                            if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z')) {
                                name.insert(std::prev(name.end()), character);
                                print_scores();
                            }
                        }
                    }
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (name.size() > 1) {
                                escape = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Escape) {
                            return;
                        }
                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (name.size() > 1) {
                                name.erase(std::prev(name.end(), 2));
                                print_scores();
                            }
                        }
                    }
                }

                if (escape) { break; }

                window.clear();
                window.draw(text);
                window.draw(*this);
                window.display();
            }

            std::ofstream fin(filename);
            for (int i = 0, size = leader_board.size(); i < size; i++) {
                fin << leader_board[i].first + " " << leader_board[i].second;
                if (i < size - 1) {
                    fin << "\n";
                }
            }
            fin.close();
        }
    }

    void LeaderBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::View view = target.getView();
        target.setView(target.getDefaultView());
        target.draw(background);
        target.draw(leaders_table);
        target.draw(scores_table);
        target.setView(view);
    }

}