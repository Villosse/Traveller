#include "mainWindow.h"

// Function to check if a point is within a rectangle
bool isMouseOverButton(const sf::RectangleShape& button, const sf::Vector2f& mousePos) {
    return button.getGlobalBounds().contains(mousePos);
}


// Function to calculate the distance between two points
float distanceBetweenPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

void init(){
    // Get the current video mode of the screen
    sf::VideoMode screenMode = sf::VideoMode::getDesktopMode();

    // Create the main window in fullscreen mode
    sf::RenderWindow window(screenMode, "Travelling Salesman Project", sf::Style::Fullscreen);

    // Define the drawing area (everything except the bottom 50 pixels for buttons)
    float buttonHeight = 50;
    float drawAreaHeight = screenMode.height - buttonHeight;
    sf::FloatRect drawArea(0, 0, screenMode.width - 200, drawAreaHeight);

    // Create buttons with dynamic width based on screen size
    float buttonWidth = (screenMode.width - 200) / 5.0f;
    std::vector<sf::RectangleShape> buttons(5);
    std::vector<std::string> buttonNames = {"Clear", "Next Step", "Final Result", "Distance : 0", "Quit"};
    std::vector<sf::Color> buttonColors = {sf::Color(230, 0, 108), sf::Color(167, 200, 14), sf::Color(0, 175, 212), sf::Color(221, 55, 55), sf::Color(245, 156, 46), sf::Color(47, 85, 117)};
    for (int i = 0; i < 5; ++i) {
        buttons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
        buttons[i].setPosition(i * buttonWidth, drawAreaHeight);
        buttons[i].setFillColor(buttonColors[i]);
    }

    // Set button texts
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return;
    }

    std::vector<sf::Text> buttonTexts(5);
    for (int i = 0; i < 5; ++i) {
        buttonTexts[i].setFont(font);
        buttonTexts[i].setString(buttonNames[i]);
        buttonTexts[i].setCharacterSize(20);
        buttonTexts[i].setFillColor(sf::Color::White);
        buttonTexts[i].setOrigin(buttonTexts[i].getLocalBounds().width / 2, buttonTexts[i].getLocalBounds().height / 2);
        buttonTexts[i].setPosition(buttons[i].getPosition() + sf::Vector2f(buttonWidth / 2, buttonHeight / 2));
    }

    // Vector to store points
    std::vector<sf::CircleShape> points;
    Line line = Line();

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse button pressed: add point if within draw area or check button click
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the click is within the drawing area
                    if (drawArea.contains(mousePos)) {
                        sf::CircleShape point(5);
                        point.setPosition(mousePos);
                        point.setFillColor(sf::Color::Black);
                        points.push_back(point);
			line.add(mousePos.x, mousePos.y);

                        // Update total distance text if there are more than two points
                        if (points.size() > 2) {
			    buttonNames[3] = "Distance : " + std::to_string(line.total_distance);
                        }
                    } else {
                        // Check button clicks
                        for (int i = 0; i < 5; ++i) {
                            if (isMouseOverButton(buttons[i], mousePos)) {
                                if (i == 0) {
                                    // Clear the drawing area if the first button is clicked
                                    points.clear();
				    buttonNames[3] = "Distance : 0";
                                } else if (i == 1) {
                                    // Handle functionality for button 2 (Next Step)
                                    // You can implement this later
                                } else if (i == 2) {
                                    // Handle functionality for button 3 (Final Result)
                                    // You can implement this later
                                } else if (i == 3) {

                                    // No action for this button as it's not clickable
                                } else if (i == 4) {
                                    // Close the window if the last button is clicked
                                    window.close();
                                }
                            }
                        }
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

        // Draw lines between consecutive points if there are more than two points
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
	    window.draw(line, 2, sf::Lines); //FIXME
        }
	
	buttonTexts[3].setString(buttonNames[3]);
        
	// Draw buttons
        for (int i = 0; i < 5; ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }

        // Update the window
        window.display();
    }
}

