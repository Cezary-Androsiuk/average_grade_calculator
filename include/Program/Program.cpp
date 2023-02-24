#include "Program.hpp"

void Program::initData(){

}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(WIDTH/2,HEIGHT/2);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(WIDTH/4,HEIGHT/4));
    this->window->setFramerateLimit(FPS);
}

void Program::initShapes(){
    this->tiles.push_back(new Tile(sf::Vector2f(20.f,50.f)));

    // this->tiles.push_back( new Tile(sf::Vector2f(20.f,50.f)));
    // this->tiles.push_back(Tile(sf::Vector2f(20.f,50.f))); // in this case objects are created again
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
            for(Tile* t : this->tiles){
                // if(t.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window)))){
                    
                // }
                if(this->currentEvent.mouseButton.button == sf::Mouse::Left)
                    t->mouseLeftPressed();
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Right)
                    t->mouseRightPressed();
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Middle)
                    t->mouseMiddlePressed();
            }
            break;
        default:
            break;
            
        }
    }
}

void Program::mouseHoverDetection(){
    for(Tile* t : this->tiles){
        if(t->getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->window))))
            t->mouseHover(true);
        else
            t->mouseHover(false);
    }
}

void Program::update(){
    this->pollEvent();

    this->mouseHoverDetection();
    for(Tile* t : this->tiles)
        t->update();
}

void Program::render(){
    this->window->clear(sf::Color::White);

    for(Tile* t : this->tiles)
        t->render(this->window);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
