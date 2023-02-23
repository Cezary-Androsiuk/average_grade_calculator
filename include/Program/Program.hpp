#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"
// cut, git init, paste, git sketch, git new branch
class Program{
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event currentEvent;


    void initData();
    void initWindow();
public:
    Program();
    ~Program();
private:
    void pollEvent();

    void update();

    void render();

    const bool running() const;
};

#endif