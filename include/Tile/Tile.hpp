#ifndef TILE_HPP
#define TILE_HPP
#include "../include.hpp"
#include "../DescriptionNotification/DescriptionNotification.hpp"

class Tile{
    sf::RectangleShape mainShape;
    bool descriptionShown;
    int mouseHoverTime;

    DescriptionNotification* message;

    void init();
    void initShape();

public:
    Tile(const sf::Vector2f&);
    ~Tile();

public:

    virtual void mouseLeftPressed();
    virtual void mouseRightPressed();
    virtual void mouseMiddlePressed();

    void update();
    void render(sf::RenderTarget*);

    sf::FloatRect getBounds() const;
    void mouseHover(const bool&);
};

#endif