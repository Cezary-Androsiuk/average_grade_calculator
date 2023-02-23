#include "Program.hpp"

void Program::initData(){

}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(WIDTH/2,HEIGHT/2);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(WIDTH/4,HEIGHT/4));
    this->window->setFramerateLimit(24);
}

void Program::initShapes(){
    this->tile = new Tile(sf::Vector2f(20.f,50.f));
}

Program::Program(){
    this->initData();
    this->initWindow();
    this->initShapes();
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
        case sf::Event::MouseButtonPressed:
            if(this->tile->getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window)))){
                if(this->currentEvent.mouseButton.button == sf::Mouse::Left)
                    this->tile->mouseLeftPressed();
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Right)
                    this->tile->mouseRightPressed();
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Middle)
                    this->tile->mouseMiddlePressed();
            }
            break;
        default:
            break;
            
        }
    }
}

void Program::update(){
    this->pollEvent();

    this->tile->update();
}

void Program::render(){
    this->window->clear(sf::Color::White);

    this->tile->render(this->window);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
