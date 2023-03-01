#include "TextTile.hpp"

void TextTile::init(){

}

void TextTile::initShape(){

}

TextTile::TextTile(const sf::Vector2f& size, const sf::Vector2f& position) : Tile(size,position){
    this->init();
    this->mainShape.setFillColor(sf::Color(120,120,120));
    this->initShape();
}
TextTile::~TextTile(){

}

void TextTile::mouseLeftPressed(){

}
void TextTile::mouseRightPressed(){

}
void TextTile::mouseMiddlePressed(){
    
}
void TextTile::mouseWheelMovedUp(){
    
}
void TextTile::mouseWheelMovedDown(){
    
}

void TextTile::update(){

}

void TextTile::render(sf::RenderTarget* window){
    
    window->draw(this->mainShape);
}

std::string TextTile::getData() const{
    return this->name;
}

void TextTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos))
        this->mouseHoverTime++;
    else 
        this->mouseHoverTime = 0;
}