#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class Program{
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event currentEvent;

    std::vector<Tile*> tiles;

    void initData();
    void initWindow();
    void initShapes();
    
    void delShapes();
public:
    Program();
    ~Program();

public:
    void pollEvent();

    void mouseHoverDetection();

    void update();
    void render();

    const bool running() const;
};

#endif