#ifndef TEXT_TILE_HPP
#define TEXT_TILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"


class TextTile : public Tile{
    std::string name;
    std::string sName;

    void init();
    void initShape();
public:
    TextTile(const sf::Vector2f&, const sf::Vector2f&);
    ~TextTile();


    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();

    void update();
    void render(sf::RenderTarget*);

    void mouseHoverInfo(const sf::Vector2f&);
};

#endif