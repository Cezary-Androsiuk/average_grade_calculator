#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"
// #include "../Tile/Tile.hpp"
#include "../GradeTile/GradeTile.hpp"
#include "../TextTile/TextTile.hpp"
#include "../EmptyTile/EmptyTile.hpp"
#include "../EdditTile/EdditTile.hpp"

class Program{
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event currentEvent;

    std::string** data;
    Tile*** tiles;
    int rows;
    int lines;

    sf::Texture gridTexture;
    sf::Texture highGradeTexture;
    sf::Texture edditTexture;
    sf::Font font;

    float gradeAvarageValueMin;
    float gradeAvarageValueMax;
    sf::Text gradeAvarageName;
    sf::Text gradeAvarageRange;
    

    void loadSources();
    void initData();
    void initWindow();
    void initShapes();
    
    void delShapes();
    void saveData();
    void deleteData();
public:
    Program();
    ~Program();

    void pollEvent();

    void mouseHoverDetection();
    bool getGradeFromSingleData(const std::string&, float&, float&) const;
    void computeGradeAvarage();
public:

    void update();
    void render();

    const bool running() const;
};

#endif