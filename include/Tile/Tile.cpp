#include "Tile.hpp"


Tile::Tile(const sf::Vector2f& size, const sf::Vector2f& position){
    this->tileType = 0; // need to be overwrite in childs classes
    this->tileSize = size;
    this->tilePosition = position;
    this->descriptionShown = false;
    this->mouseHoverTime = 0;
    this->mainShape = sf::RectangleShape(size);
    this->mainShape.setPosition(position);
    this->mainShape.setFillColor(sf::Color(200,200,200));
}

Tile::~Tile(){

}

sf::Vector2f Tile::localPosition_to_globalPosition(const sf::Vector2f& localPos) const{
    sf::Vector2f globalPos;
    globalPos.x = localPos.x + this->tilePosition.x;
    globalPos.y = localPos.y + this->tilePosition.y;
    return globalPos;
}
sf::Vector2f Tile::globalPosition_to_localPosition(const sf::Vector2f& globalPos) const{
    sf::Vector2f localPos;
    localPos.x = globalPos.x - this->tilePosition.x;
    localPos.y = globalPos.y - this->tilePosition.y;
    return localPos;
}