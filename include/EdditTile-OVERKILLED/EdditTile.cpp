#include "EdditTile.hpp"


void EdditTile::interpretData(const std::string& rawData){
    // std::string text = rawData;
    // text.erase(text.begin());
    this->columns = atoi(rawData.substr(1, rawData.length()-1).c_str());
}

EdditTile::EdditTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Texture& texture) : Tile(size, position){
    this->tileType = 3;
    this->mainShape.setFillColor(sf::Color::Red);
}
EdditTile::~EdditTile(){

}


void EdditTile::mouseLeftPressed(){

}
void EdditTile::mouseRightPressed(){

}
void EdditTile::mouseMiddlePressed(){
    
}
void EdditTile::mouseWheelMovedUp(){
    
}
void EdditTile::mouseWheelMovedDown(){
    
}
void EdditTile::keyboardKeys(const sf::Keyboard::Key&){
    // none
}


void EdditTile::update(){
    
}
void EdditTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
    // window->draw(this->edditSign);
}


std::string EdditTile::getData() const{
    return std::string("+") + std::to_string(this->columns);
}
void EdditTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos))
        this->mouseHoverTime++;
    else
        this->mouseHoverTime = 0;
}