#include "GradeTile.hpp"

void GradeTile::init(){
    this->tileType = 1;
    this->enabled = 0;
    for(int i=0; i<5; i++)
        this->expectedGradesStatus[i] = false;
    this->grade = 0;
}

void GradeTile::initTextures(){
    if(this->grid.texture.loadFromFile("src/tile_template.png"))
        printf("can't load texture in path \"src/tile_template.png\"\n");
    this->grid.texture.setSmooth(false);
    this->grid.texture.setRepeated(false);
    this->grid.sprite.setTexture(this->grid.texture);

    // if(this->expectedGrades->texture.loadFromFile("src/color1.png"))
    //     printf("can't load texture in path \"src/color1.png\"\n");
    // this->expectedGrades.texture.setSmooth(false);
    // this->expectedGrades.texture.setSmooth(false);
}

void GradeTile::initShapes(){
    this->mainShape.setFillColor(sf::Color(160,160,160));
    
    this->grid.sprite.setPosition(this->mainShape.getPosition());
    this->grid.sprite.setScale(sf::Vector2f(2.f, 2.f));
}

GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position) : Tile(size, position){
    this->init();
    this->initTextures();
    this->initShapes();
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
    // if is on grade part
    if(this->grade >= 6) this->grade = 0;
    else this->grade ++;
}
void GradeTile::mouseWheelMovedDown(const sf::Vector2f& mousePos){
    // if is on grade part
    if(this->grade <= 0) this->grade = 6;
    else this->grade --;
}

void GradeTile::update(){

}

void GradeTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
    window->draw(this->grid.sprite);
}
