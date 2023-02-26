#include "TextTile.hpp"

TextTile::TextTile(const sf::Vector2f& size, const sf::Vector2f& position) : Tile(size,position){
    this->mainShape.setFillColor(sf::Color(120,120,120));
}
TextTile::~TextTile(){

}

void TextTile::mouseLeftPressed(const sf::Vector2f& mousePos){

}
void TextTile::mouseRightPressed(const sf::Vector2f& mousePos){

}
void TextTile::mouseMiddlePressed(const sf::Vector2f& mousePos){
    
}
void TextTile::mouseWheelMovedUp(const sf::Vector2f& mousePos){
    
}
void TextTile::mouseWheelMovedDown(const sf::Vector2f& mousePos){
    
}

void TextTile::update(){

}

void TextTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
}
