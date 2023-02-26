#ifndef TEXT_TILE_HPP
#define TEXT_TILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"


class TextTile : public Tile{
    std::string name;
    std::string sName;

public:
    TextTile(const sf::Vector2f&, const sf::Vector2f&);
    ~TextTile();


    void mouseLeftPressed(const sf::Vector2f& mousePos);
    void mouseRightPressed(const sf::Vector2f& mousePos);
    void mouseMiddlePressed(const sf::Vector2f& mousePos);
    void mouseWheelMovedUp(const sf::Vector2f& mousePos);
    void mouseWheelMovedDown(const sf::Vector2f& mousePos);

    void update();
    void render(sf::RenderTarget*);

};

#endif