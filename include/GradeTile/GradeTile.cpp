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


void GradeTile::mouseLeftPressed(const sf::Vector2f& mousePos){
    if(this->mouseHoverTime != 0){
        std::cout << "x: " << this->objectRelativePosition(mousePos).x << " y: " <<
        this->objectRelativePosition(mousePos).y << "\n";
    }
}
void GradeTile::mouseRightPressed(const sf::Vector2f& mousePos){
    
}
void GradeTile::mouseMiddlePressed(const sf::Vector2f& mousePos){
    
}
void GradeTile::mouseWheelMovedUp(const sf::Vector2f& mousePos){
    
}
void GradeTile::mouseWheelMovedDown(const sf::Vector2f& mousePos){
    
}

void GradeTile::update(){

}

void GradeTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
}
