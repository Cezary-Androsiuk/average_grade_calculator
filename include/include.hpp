#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <vector>
#include <fstream>
#include <sstream>
    #include <iostream> // to delete

#define FPS 25
#define MAIN_WINDOW_WIDTH 1920
#define MAIN_WINDOW_HEIGHT 1080

#define TILE_WIDTH 122.f
#define TILE_HEIGHT 122.f
// #define TILE_SIZE sf::Vector2f(TILE_WIDTH, TILE_HEIGHT)

#define TILE_SEPARATOR 2.f

#define WINDOW_TOP_MARGIN 100.f
#define WINDOW_BOTTOM_MARGIN 10.f
#define WINDOW_LEFT_MARGIN 10.f
#define WINDOW_RIGHT_MARGIN 10.f
// #define TILE_POSITION sf::Vector2f(WINDOW_LEFT_MARGIN + TILE_WIDTH*i + TILE_SEPARATOR*i, WINDOW_TOP_MARGIN + TILE_HEIGHT*j + TILE_SEPARATOR*j)

#define HOVER_DESCRIPTION_ENABLED true
#define DATA_FILE "data.txt"

#endif



