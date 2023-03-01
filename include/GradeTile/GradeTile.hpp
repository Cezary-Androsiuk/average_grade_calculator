#ifndef GRADETILE_HPP
#define GRADETILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class GradeTile : public Tile{

    sf::FloatRect mouseUpdateAreaOnTile[6] ={
        sf::FloatRect(0.f, 0.f, 25.f, 18.f),
        sf::FloatRect(25.f, 0.f, 24.f, 18.f),
        sf::FloatRect(49.f, 0.f, 24.f, 18.f),
        sf::FloatRect(73.f, 0.f, 24.f, 18.f),
        sf::FloatRect(97.f, 0.f, 25.f, 18.f),
        sf::FloatRect(0.f, 18.f, 122.f, 104.f)
    };

    struct{
        bool enabled;
        bool expectedGrade[5];
        int grade; // {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} => {-, 2, 2.5, 2.75, 3, 3.25, 3.5, 4, 4.5, 5}
        int grade_type; // 1 gray, 2 red
    } data;
    int mouseHoverOnPart; // 0 none, 1-5 expectedGrade, 6 grade

    sf::Sprite grid;
    sf::Sprite grade;
    sf::RectangleShape expectedGrades[5];
    // sf::RectangleShape disableBlocker;

    void init();
    void interpretData(const std::string&);
    void initTextures(const sf::Texture&, const sf::Texture&);
    void initShapes();
public:
    GradeTile(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Texture&, const sf::Texture&);
    ~GradeTile();

    void updateGradeTexture();

    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();

    void update();
    void render(sf::RenderTarget*);

    void setValues();
    void getValues();

    void mouseHoverInfo(const sf::Vector2f&);
};

#endif