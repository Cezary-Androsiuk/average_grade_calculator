#ifndef TEXT_TILE_HPP
#define TEXT_TILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"


class TextTile : public Tile{
    std::string name;
    // std::wstring name;
    // std::string sName;

    sf::Text text;

    void init();
    void interpretData(const std::string&);
    void initText(const sf::Font&);
    void initShape();
public:
    TextTile(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Font&);
    ~TextTile();


    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();
    void keyboardKeys(const sf::Keyboard::Key&);

    void update();
    void render(sf::RenderTarget*);

    std::string getData() const;

    void mouseHoverInfo(const sf::Vector2f&);
};

#endif