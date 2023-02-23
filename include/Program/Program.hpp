#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class Program{
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event currentEvent;

    Tile* tile;

    void initData();
    void initWindow();
    void initShapes();
public:
    Program();
    ~Program();

public:
    void pollEvent();

    void update();
    void render();

    const bool running() const;
};

#endif