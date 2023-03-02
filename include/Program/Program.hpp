#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"
// #include "../Tile/Tile.hpp"
#include "../GradeTile/GradeTile.hpp"
#include "../TextTile/TextTile.hpp"

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
    sf::Font font;

    void loadTextures();
    void initData();
    void initWindow();
    void initShapes();
    
    void exitApp();
    void delShapes();
    void saveData();
    void deleteData();
public:
    Program();
    ~Program();

public:
    void pollEvent();

    void mouseHoverDetection();

    void update();
    void render();

    const bool running() const;
};

#endif