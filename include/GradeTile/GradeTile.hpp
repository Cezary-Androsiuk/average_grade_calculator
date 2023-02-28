#ifndef GRADETILE_HPP
#define GRADETILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class GradeTile : public Tile{
    #define AREA_EXPECTED_GRADE_3__FR sf::FloatRect(0.f, 0.f, 25.f, 18.f)
    #define AREA_EXPECTED_GRADE_35_FR sf::FloatRect(25.f, 0.f, 24.f, 18.f)
    #define AREA_EXPECTED_GRADE_4__FR sf::FloatRect(49.f, 0.f, 24.f, 18.f)
    #define AREA_EXPECTED_GRADE_45_FR sf::FloatRect(73.f, 0.f, 24.f, 18.f)
    #define AREA_EXPECTED_GRADE_5__FR sf::FloatRect(97.f, 0.f, 25.f, 18.f)
    #define AREA_GRADE_FR sf::FloatRect(0.f, 18.f, 122.f, 104.f)

    struct{
        bool enabled;
        bool expectedGrade[5];
        int grade; // {0, 1, 2, 3, 4, 5, 6} => {-, 2, 3, 3.5, 4, 4.5, 5}
        int grade_type; // 1 red, 2 gray
    } data;
    int mouseHoverType; // 0 none, 1-5 expectedGrade, 6 grade

    sf::Sprite grid;
    sf::Sprite grade;
    sf::RectangleShape expectedGrades[5];
    bool gradeVisible;

    void init();
    void interpretData(const std::string&);
    void initTextures(const sf::Texture&, const sf::Texture&, const sf::Texture&);
    void initShapes();
public:
    GradeTile(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Texture&, const sf::Texture&, const sf::Texture&);
    ~GradeTile();

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