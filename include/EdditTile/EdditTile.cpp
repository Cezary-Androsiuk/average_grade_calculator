#include "EdditTile.hpp"

EdditTile::EdditTile(const sf::Vector2f& size,const sf::Vector2f& position, const sf::Texture& texture) : Tile(size, position){
    this->tileType = 3;
}
EdditTile::~EdditTile(){

}


void EdditTile::mouseLeftPressed(){

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
void EdditTile::keyboardKeys(const sf::Keyboard::Key&){
    // none
}

void EdditTile::update(){
    
}
void EdditTile::render(sf::RenderTarget*){
    // none
}

std::string EdditTile::getData() const{
    return "+";
}
void EdditTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos))
        this->mouseHoverTime++;
    else
        this->mouseHoverTime = 0;
}