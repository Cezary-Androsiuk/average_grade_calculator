#include "Tile.hpp"


Tile::Tile(const sf::Vector2f& size, const sf::Vector2f& position){
    this->descriptionShown = false;
    this->mouseHoverTime = 0;
    this->mainShape = sf::RectangleShape(size);
    this->mainShape.setPosition(position);
    this->mainShape.setFillColor(sf::Color(200,200,200));
}

Tile::~Tile(){

}

sf::Vector2f Tile::objectRelativePosition(const sf::Vector2f& absolutePosition) const{
    sf::Vector2f relative;
    relative.x = absolutePosition.x - this->mainShape.getPosition().x;
    relative.y = absolutePosition.y - this->mainShape.getPosition().y;
    return relative;
}

sf::FloatRect Tile::getBounds() const{
    return this->mainShape.getGlobalBounds();
}

void Tile::mouseHover(const bool& visible){
    if(visible) this->mouseHoverTime++;
    else this->mouseHoverTime = 0;
}