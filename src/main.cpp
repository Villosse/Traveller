#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Line.h"
#include "Travelling_salesman_problem.h"
#include "Genetic_algorithm.h"

bool isMouseOverButton(const sf::RectangleShape& button, const sf::Vector2f& mousePos) {
    return button.getGlobalBounds().contains(mousePos);
}
int main() {
    // Get the current video mode of the screen
    sf::VideoMode screenMode = sf::VideoMode::getDesktopMode();

    // Create the main window in fullscreen mode
    sf::RenderWindow window(screenMode, "SFML Application", sf::Style::Fullscreen);

    // Define the drawing area (everything except the bottom 100 pixels for buttons)
    float buttonHeight = 50;
    float drawAreaHeight = screenMode.height - buttonHeight;
    sf::FloatRect drawArea(0, 0, screenMode.width, drawAreaHeight);

    // Create buttons with dynamic width based on screen size
    float buttonWidth = screenMode.width / 4.0f;
    sf::RectangleShape button1(sf::Vector2f(buttonWidth, buttonHeight));
    sf::RectangleShape button2(sf::Vector2f(buttonWidth, buttonHeight));
    sf::RectangleShape button3(sf::Vector2f(buttonWidth, buttonHeight));

    // Set button positions
    button1.setPosition(screenMode.width / 4.0f - buttonWidth / 2.0f, drawAreaHeight + 10);
    button2.setPosition(screenMode.width / 2.0f - buttonWidth / 2.0f, drawAreaHeight + 10);
    button3.setPosition(3 * screenMode.width / 4.0f - buttonWidth / 2.0f, drawAreaHeight + 10);

    // Set button colors
    button1.setFillColor(sf::Color::Red);
    button2.setFillColor(sf::Color::Green);
    button3.setFillColor(sf::Color::Blue);

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return -1;
    }

    // Create text labels for the buttons
    sf::Text text1("Clear", font, 20);
    sf::Text text2("Calculate size", font, 20);
    sf::Text text3("Debug", font, 20);

    // Set text positions (centered on the buttons)
    text1.setPosition(button1.getPosition().x + buttonWidth / 2.0f - text1.getGlobalBounds().width / 2.0f, drawAreaHeight + 20);
    text2.setPosition(button2.getPosition().x + buttonWidth / 2.0f - text2.getGlobalBounds().width / 2.0f, drawAreaHeight + 20);
    text3.setPosition(button3.getPosition().x + buttonWidth / 2.0f - text3.getGlobalBounds().width / 2.0f, drawAreaHeight + 20);

    // Set text colors
    text1.setFillColor(sf::Color::White);
    text2.setFillColor(sf::Color::White);
    text3.setFillColor(sf::Color::White);

    // Vector to store points
    std::vector<sf::CircleShape> points;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse button pressed: add point if within draw area
            if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (drawArea.contains(mousePos)) {
                        sf::CircleShape point(5);
                        point.setPosition(mousePos);
                        point.setFillColor(sf::Color::Black);
                        points.push_back(point);
                    } 
		    else if (isMouseOverButton(button1, mousePos)) {
                        // Clear the drawing area if the first button is clicked
                        points.clear();
                    }
		    else if (isMouseOverButton(button3, mousePos)){
		      std::cout << "Points coordinates:" << std::endl;
                        for (const auto& point : points) {
                            sf::Vector2f pos = point.getPosition();
                            std::cout << "Point at (" << pos.x << ", " << pos.y << ")" << std::endl;
                        }  
		    }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw all points
        for (const auto& point : points) {
            window.draw(point);
        }

        // Draw buttons
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);

        // Draw text labels
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);

	if (points.size() > 2) {
            for (size_t i = 1; i < points.size(); ++i) {
                sf::Vector2f p1 = points[i - 1].getPosition();
                sf::Vector2f p2 = points[i].getPosition();
                sf::Vertex line[] = {
                    sf::Vertex(p1, sf::Color::Black),
                    sf::Vertex(p2, sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);
            }
	    sf::Vector2f p1 = points[0].getPosition();
	    sf::Vector2f p2 = points[points.size() - 1].getPosition();
	    sf::Vertex line[] = {
	      sf::Vertex(p1, sf::Color::Black),
	      sf::Vertex(p2, sf::Color::Black)
	    };
	    window.draw(line, 2, sf::Lines);
        }

        // Update the window
        window.display();
    }

    return 0;
}
