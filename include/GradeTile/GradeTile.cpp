#include "GradeTile.hpp"

void GradeTile::init(){
    this->enabled = 0;
    for(int i=0; i<5; i++)
        this->expected_grades[i] = false;
    this->grade = 0;
}

void GradeTile::initShape(){

}

GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position) : Tile(size, position){
    this->init();
    this->mainShape.setFillColor(sf::Color(160,160,160));
}

GradeTile::~GradeTile(){

}


sf::Vector2f GradeTile::objectRelativePosition(const sf::Vector2f& absolutePosition) const{
    sf::Vector2f relative;
    relative.x = absolutePosition.x - this->mainShape.getPosition().x;
    relative.y = absolutePosition.y - this->mainShape.getPosition().y;
    return relative;
}
std::string GradeTile::mouseLeftPressed(const sf::Vector2f& mousePos){
    if(this->mouseHoverTime != 0){
        std::cout << "x: " << this->objectRelativePosition(mousePos).x << " y: " <<
        this->objectRelativePosition(mousePos).y << "\n";
    }
    return "0";
}
std::string GradeTile::mouseRightPressed(const sf::Vector2f& mousePos){
    return "0";
}
std::string GradeTile::mouseMiddlePressed(const sf::Vector2f& mousePos){
    return "0";
}