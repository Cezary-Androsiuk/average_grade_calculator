#ifndef EDDITTILE_HPP
#define EDDITTILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class EdditTile : public Tile{
    sf::Sprite addSign;
public:
    EdditTile(const sf::Vector2f&,const sf::Vector2f&);
    ~EdditTile();
public:
    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();

    void update();
    void render(sf::RenderTarget*);

    std::string getData() const;
    void mouseHoverInfo(const sf::Vector2f& mousePos);
};


#endif