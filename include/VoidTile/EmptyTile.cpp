#include "EmptyTile.hpp"

EmptyTile::EmptyTile(const sf::Vector2f& size,const sf::Vector2f& position) : Tile(size, position){
    this->tileType = 3;
}
EmptyTile::~EmptyTile(){
    
}

void EmptyTile::mouseLeftPressed(){
    //none
}
void EmptyTile::mouseRightPressed(){
    // none
}
void EmptyTile::mouseMiddlePressed(){
    // none
}
void EmptyTile::mouseWheelMovedUp(){
    // none
}
void EmptyTile::mouseWheelMovedDown(){
    // none
}

void EmptyTile::update(){
    
}
void EmptyTile::render(sf::RenderTarget*){
    // none
}

std::string EmptyTile::getData() const{
    return "VOID";
}
void EmptyTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    // none
}