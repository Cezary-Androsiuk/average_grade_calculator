#ifndef GRADETILE_HPP
#define GRADETILE_HPP
#include "../include.hpp"
#include "../Tile/Tile.hpp"

class GradeTile : public Tile{

    std::vector<const sf::FloatRect*> mouseActionsAreasOnTile;

    struct{
        bool enabled;
        bool locked;
        bool expectedGrade[5];
        int grade; // {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} => {-, 2, 2.5, 2.75, 3, 3.25, 3.5, 4, 4.5, 5}
        // int grade; // {0, 1, 2, 3, 4, 5, 6} => {-, 2, 3, 3.5, 4, 4.5, 5}
        // bool grade2;
        int grade_type; // 1 gray, 2 red
    } data;
    int mouseHoverOnPart; // 0 none, 1-5 expectedGrade, 8 lock, 7 grade

#if DRAW_MOUSE_ACTIONS_AREAS_ON_TILE == 1
    std::vector<sf::RectangleShape*> mouseActionsAreasOnTile_asRectangle;
#endif

    sf::Sprite tileTemplate;
    sf::Sprite currentGrade;
    sf::Sprite expectedGrade[5];

    void init();
    void interpretData(const std::string&);
    void initTextures(const sf::Texture&, const sf::Texture&, const sf::Texture&);
    void initShapes();
public:
    GradeTile(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Texture&, const sf::Texture&, const sf::Texture&);
    ~GradeTile();

    void updateTileTemplateTexture();
    void updateExpectedGradeTexture();
    void updateCurrentGradeTexture();

    void mouseLeftPressed();
    void mouseRightPressed();
    void mouseMiddlePressed();
    void mouseWheelMovedUp();
    void mouseWheelMovedDown();

    void update();
    void render(sf::RenderTarget*);
    
    std::string getData() const;

    void mouseHoverUpdate(const sf::Vector2f&);
};

#endif