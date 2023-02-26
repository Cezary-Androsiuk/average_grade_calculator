#include "Tile.hpp"

void Tile::init(){
    this->descriptionShown = false;
    this->mouseHoverTime = 0;
}

void Tile::initShape(){

}


Tile::Tile(const sf::Vector2f& size, const sf::Vector2f& position){
    this->init();
    this->mainShape = sf::RectangleShape(size);
    this->mainShape.setPosition(position);
    this->mainShape.setFillColor(sf::Color(200,200,200));
}

Tile::~Tile(){
}


// void Tile::mouseLeftPressed(const sf::Vector2f& mousePos){
//     printf("Left Key was Pressed!\n");
// }

// void Tile::mouseRightPressed(const sf::Vector2f& mousePos){
//     printf("Right Key was Pressed!\n");
// }

// void Tile::mouseMiddlePressed(const sf::Vector2f& mousePos){
//     printf("Middle Key was Pressed!\n");
// }

void Tile::update(){

}

void Tile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
}

sf::FloatRect Tile::getBounds() const{
    return this->mainShape.getGlobalBounds();
}

void Tile::mouseHover(const bool& visible){
    if(visible) this->mouseHoverTime++;
    else this->mouseHoverTime = 0;
}