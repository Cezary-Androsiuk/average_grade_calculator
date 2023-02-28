#ifndef GRADETILE_HPP
#define GRADETILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class GradeTile : public Tile{
    struct{
        bool enabled;
        bool expectedGrade[5];
        int grade; // {0, 1, 2, 3, 4, 5, 6} => {-, 2, 3, 3.5, 4, 4.5, 5}
        int grade_type; // 1 red, 2 gray
    } data;
    
    sf::Sprite grid;
    sf::Sprite expectedGrades[5];
    sf::Sprite grade;

    void init();
    void interpretData(const std::string&);
    void initTextures(const sf::Texture&, const sf::Texture&, const sf::Texture&);
    void initShapes();
public:
    GradeTile(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Texture&, const sf::Texture&, const sf::Texture&);
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