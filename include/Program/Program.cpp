#include "Program.hpp"

void Program::initData(){

}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(WIDTH/2,HEIGHT/2);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(WIDTH/4,HEIGHT/4));
    this->window->setFramerateLimit(24);
}

Program::Program(){
    this->initData();
    this->initWindow();
}

Program::~Program(){
    delete this->window;
}

void Program::pollEvent(){
    while(this->window->pollEvent(this->currentEvent)){
        switch (this->currentEvent.type){
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->currentEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
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
    this->window->clear(sf::Color::White);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
