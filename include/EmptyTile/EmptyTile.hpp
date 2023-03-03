#ifndef EMPTYTILE_HPP
#define EMPTYTILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class EmptyTile : public Tile{

public:
    EmptyTile(const sf::Vector2f&,const sf::Vector2f&);
    ~EmptyTile();
public:
    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();
    void keyboardKeys(const sf::Keyboard::Key&);

    void update();
    void render(sf::RenderTarget*);

    std::string getData() const;
    void mouseHoverInfo(const sf::Vector2f& mousePos);
};

#endif