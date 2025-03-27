#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include "lovia_interpreter.h"

using namespace std;

class LoviaGUI {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text inputText;
    sf::Text outputText;
    sf::RectangleShape inputBox;
    sf::RectangleShape runButton;
    sf::Text runButtonText;
    string userInput;
    LoviaInterpreter interpreter;

public:
    LoviaGUI() : window(sf::VideoMode(600, 400), "Lovia Interpreter") {
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font!" << endl;
        }

        inputBox.setSize(sf::Vector2f(500, 40));
        inputBox.setPosition(50, 50);
        inputBox.setFillColor(sf::Color(200, 200, 200));

        inputText.setFont(font);
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(60, 60);

        runButton.setSize(sf::Vector2f(100, 40));
        runButton.setPosition(250, 120);
        runButton.setFillColor(sf::Color(100, 200, 100));

        runButtonText.setFont(font);
        runButtonText.setCharacterSize(20);
        runButtonText.setFillColor(sf::Color::Black);
        runButtonText.setString("Run");
        runButtonText.setPosition(275, 130);

        outputText.setFont(font);
        outputText.setCharacterSize(20);
        outputText.setFillColor(sf::Color::White);
        outputText.setPosition(50, 200);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8 && !userInput.empty()) {
                            userInput.pop_back();
                        } else if (event.text.unicode != 8) {
                            userInput += static_cast<char>(event.text.unicode);
                        }
                        inputText.setString(userInput);
                    }
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        if (runButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            stringstream ss(userInput);
                            vector<string> lines;
                            string line;
                            while (getline(ss, line)) {
                                lines.push_back(line);
                            }
                            interpreter.execute(lines);
                            outputText.setString("Executed successfully!");
                        }
                    }
                }
            }

            window.clear(sf::Color(50, 50, 50));
            window.draw(inputBox);
            window.draw(inputText);
            window.draw(runButton);
            window.draw(runButtonText);
            window.draw(outputText);
            window.display();
        }
    }
};

int main() {
    LoviaGUI gui;
    gui.run();
    return 0;
}
