#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "../include.hpp"

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

public:
    void pollEvent();

    void update();

    void render();

    const bool running() const;
};

#endif