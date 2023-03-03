#include "EdditTile.hpp"

EdditTile::EdditTile(const sf::Vector2f& size,const sf::Vector2f& position) : Tile(size, position){
    this->tileType = 3;
}
EdditTile::~EdditTile(){
    
}


void EdditTile::mouseLeftPressed(){
    //none
}
void EdditTile::mouseRightPressed(){
    // none
}
void EdditTile::mouseMiddlePressed(){
    // none
}
void EdditTile::mouseWheelMovedUp(){
    // none
}
void EdditTile::mouseWheelMovedDown(){
    // none
}

void EdditTile::update(){
    
}
void EdditTile::render(sf::RenderTarget*){
    // none
}

std::string EdditTile::getData() const{
    return "VOID";
}
void EdditTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    // none
}