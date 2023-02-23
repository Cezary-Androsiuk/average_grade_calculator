#ifndef TILE_HPP
#define TILE_HPP
#include "../include.hpp"

class Tile{
    sf::RectangleShape mainShape;

    void initShape();

public:
    // Tile();
    Tile(sf::Vector2f);
    ~Tile();

public:
    void pollEvent();

    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();

    void update();
    void render(sf::RenderTarget*);

    sf::FloatRect getBounds() const;
};

#endif