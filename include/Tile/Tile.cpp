#include "Tile.hpp"

void Tile::initShape(){

}

// Tile::Tile(){
//     Tile(sf::Vector2f(width,height));
// }

Tile::Tile(sf::Vector2f size){
    // this->initShape();
    // this->shape->setSize(size);
    this->mainShape = sf::RectangleShape(size);
    this->mainShape.setFillColor(sf::Color(20,20,180));
    this->mainShape.setPosition(sf::Vector2f(60.f,50.f));
}

Tile::~Tile(){
}

void Tile::pollEvent(){

}

void Tile::mouseLeftPressed(){
    printf("Left Key was Pressed!\n");
}

void Tile::mouseRightPressed(){
    printf("Right Key was Pressed!\n");
}

void Tile::mouseMiddlePressed(){
    printf("Middle Key was Pressed!\n");
}

void Tile::update(){

}

void Tile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
}

sf::FloatRect Tile::getBounds() const{
    return this->mainShape.getGlobalBounds();
}