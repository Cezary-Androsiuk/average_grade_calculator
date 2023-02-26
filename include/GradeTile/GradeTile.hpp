#ifndef GRADETILE_HPP
#define GRADETILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class GradeTile : public Tile{
    bool enabled;
    bool expected_grades[5];
    int grade; // {1, 2, 3, 4, 5} => {3, 3.5, 4, 4.5, 5}
    int grade_type; // 1 red, 2 gray

    void init();
    void initShape();
public:
    GradeTile(const sf::Vector2f&, const sf::Vector2f&);
    ~GradeTile();

    void mouseLeftPressed(const sf::Vector2f& mousePos);
    void mouseRightPressed(const sf::Vector2f& mousePos);
    void mouseMiddlePressed(const sf::Vector2f& mousePos);
    void mouseWheelMovedUp(const sf::Vector2f& mousePos);
    void mouseWheelMovedDown(const sf::Vector2f& mousePos);

    void update();
    void render(sf::RenderTarget*);

    void setValues();
    void getValues();
};

#endif