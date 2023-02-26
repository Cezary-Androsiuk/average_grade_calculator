#ifndef GRADETILE_HPP
#define GRADETILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class GradeTile : public Tile{
    bool enabled;
    bool expected_grades[5];
    int grade; // {1, 2, 3, 4, 5} => {3, 3.5, 4, 4.5, 5}

    void init();
    void initShape();
public:
    GradeTile(const sf::Vector2f&, const sf::Vector2f&);
    ~GradeTile();

    sf::Vector2f objectRelativePosition(const sf::Vector2f&) const;
    std::string mouseLeftPressed(const sf::Vector2f& mousePos);
    std::string mouseRightPressed(const sf::Vector2f& mousePos);
    std::string mouseMiddlePressed(const sf::Vector2f& mousePos);

    void setValues();
};

#endif