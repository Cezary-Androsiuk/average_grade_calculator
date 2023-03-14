#ifndef TEXT_TILE_HPP
#define TEXT_TILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"


class TextTile : public Tile{
    std::string data;

    std::vector<sf::Text*> text_vector;
    std::vector<sf::RectangleShape*> text_vector_globalBounds;
    unsigned int charSize;

    void init();
    void interpretData(const std::string&);
    void initText(const sf::Font&, const unsigned int&);
    void initShape();
public:
    TextTile(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Font&, const unsigned int&);
    ~TextTile();

    void updateTextPosition();

    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();
    void keyboardKeys(const sf::Keyboard::Key&);

    void update();
    void render(sf::RenderTarget*);

    std::string getData() const;

    void mouseHoverUpdate(const sf::Vector2f&);
};

#endif