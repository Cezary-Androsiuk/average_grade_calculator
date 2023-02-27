#ifndef TILE_HPP
#define TILE_HPP
#include "../include.hpp"
#include "../DescriptionNotification/DescriptionNotification.hpp"

class Tile{
protected:
    int tileType; // {0, 1, 2, 3} => {Tile, GradeTile, TextTile, EmptyTile}
    sf::RectangleShape mainShape;
    bool descriptionShown;
    int mouseHoverTime;

    DescriptionNotification* message;

public:
    Tile(const sf::Vector2f&,const sf::Vector2f&);
    ~Tile();

public:

    sf::Vector2f objectRelativePosition(const sf::Vector2f&) const;
    virtual void mouseLeftPressed(const sf::Vector2f& mousePos) = 0;
    virtual void mouseRightPressed(const sf::Vector2f& mousePos) = 0;
    virtual void mouseMiddlePressed(const sf::Vector2f& mousePos) = 0;
    virtual void mouseWheelMovedUp(const sf::Vector2f& mousePos) = 0;
    virtual void mouseWheelMovedDown(const sf::Vector2f& mousePos) = 0;

    virtual void update() = 0;
    virtual void render(sf::RenderTarget*) = 0;

    sf::FloatRect getBounds() const;
    void mouseHover(const bool&);
};

#endif