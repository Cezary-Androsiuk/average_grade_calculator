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
    virtual void mouseLeftPressed() = 0;
    virtual void mouseRightPressed() = 0;
    virtual void mouseMiddlePressed() = 0;
    virtual void mouseWheelMovedUp() = 0;
    virtual void mouseWheelMovedDown() = 0;

    virtual void update() = 0;
    virtual void render(sf::RenderTarget*) = 0;

    virtual std::string getData() const = 0;
    virtual void mouseHoverInfo(const sf::Vector2f& mousePos) = 0;
};

#endif