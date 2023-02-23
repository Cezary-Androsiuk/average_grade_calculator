#include "Program.hpp"

void Program::initData(){

}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(1920,1080,16);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Fullscreen);
    this->window->setFramerateLimit(30);
}

Program::Program(){
    this->initData();
    this->initWindow();
}

Program::~Program(){
    delete this->window;
}

void Program::pollEvent(){
    while(this->window->pollEvent(this->currentEvent))
    {
        switch (this->currentEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->currentEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
            if(this->currentEvent.key.code == sf::Keyboard::Space)
                this->startGame = true;
            break;
        default:
            break;
        }
    }
}

void Program::update(){
    this->pollEvent();
}

void Program::render(){
    this->window->clear();

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
