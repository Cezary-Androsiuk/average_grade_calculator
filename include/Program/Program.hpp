#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"
// #include "../Tile/Tile.hpp"
#include "../GradeTile/GradeTile.hpp"
#include "../TextTile/TextTile.hpp"
#include "../EmptyTile/EmptyTile.hpp"

class Program{
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event currentEvent;

    std::string** data;
    Tile*** tiles;
    int rows;
    int lines;
    unsigned int windowWidth;
    unsigned int windowHeight;

    sf::Texture tileTemplateTexture;
    sf::Texture expectedGradeTexture;
    sf::Texture currentGradeTexture;
    sf::Font font;

    float gradeAvarageValueMin;
    float gradeAvarageValueMax;
    sf::Text gradeAvarageName;
    sf::Text gradeAvarageRange;
    

    void loadSources();
    void initData();
    void initShapes();
    void initWindow();
    
    void delShapes();
    void saveData();
    void deleteData();
public:
    Program();
    ~Program();

    void pollEvent();
    
    void updateData();
    void updateText();
    void mouseHoverDetection();
    bool getGradeFromSingleData(const std::string&, float&, float&) const;
    void computeGradeAvarage();
public:

    void update();
    void render();

    const bool running() const;
};

#endif