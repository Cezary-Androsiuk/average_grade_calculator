#ifndef TILE_HPP
#define TILE_HPP
#include "../include.hpp"
#include "../DescriptionNotification/DescriptionNotification.hpp"

class Tile{
protected:
    sf::RectangleShape mainShape;
    bool descriptionShown;
    int mouseHoverTime;

    DescriptionNotification* message;

    void init();
    void initShape();

public:
    Tile(const sf::Vector2f&,const sf::Vector2f&);
    ~Tile();

public:

    virtual sf::Vector2f objectRelativePosition(const sf::Vector2f&) const = 0;
    virtual std::string mouseLeftPressed(const sf::Vector2f& mousePos) = 0;
    virtual std::string mouseRightPressed(const sf::Vector2f& mousePos) = 0;
    virtual std::string mouseMiddlePressed(const sf::Vector2f& mousePos) = 0;

    void update();
    void render(sf::RenderTarget*);

    sf::FloatRect getBounds() const;
    void mouseHover(const bool&);
};

#endif