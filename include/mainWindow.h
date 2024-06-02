#pragma once

#ifndef MAIN_WINDOW_H

#define MAIN_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "Line.h"

// Function to check if a point is within a rectangle
bool isMouseOverButton(const sf::RectangleShape& button, const sf::Vector2f& mousePos);

// Function to calculate the distance between two points
float distanceBetweenPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);

void init();

#endif
