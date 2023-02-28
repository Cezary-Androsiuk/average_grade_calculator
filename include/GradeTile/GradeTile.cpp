#include "GradeTile.hpp"

void GradeTile::init(){
    this->tileType = 1;
    this->data.enabled = 0;
    for(int i=0; i<5; i++)
        this->data.expectedGrade[i] = false;
    this->data.grade = 0;
    this->gradeVisible = false;
}

void GradeTile::interpretData(const std::string& rawData){

}

void GradeTile::initTextures(const sf::Texture& gridTexture, const sf::Texture& lowGradeTexture, const sf::Texture& highGradeTexture){
    this->grid.setTexture(gridTexture);

    this->grade.setTexture(highGradeTexture);
    // if(this->expectedGrades->texture.loadFromFile("src/color1.png"))
    //     printf("can't load texture in path \"src/color1.png\"\n");
    // this->expectedGrades.texture.setSmooth(false);
    // this->expectedGrades.texture.setSmooth(false);
}

void GradeTile::initShapes(){
    this->mainShape.setFillColor(sf::Color(160,160,160));
    
    this->grid.setPosition(this->mainShape.getPosition());
    this->grid.setScale(sf::Vector2f(2.f, 2.f));

    this->grade.setPosition(sf::Vector2f(this->mainShape.getPosition().x + 10.f, this->mainShape.getPosition().y + 20.f));
    this->grade.setScale(sf::Vector2f(2.f, 2.f));
    this->grade.setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(40,25)));
}

GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& data, const sf::Texture& gridTexture, const sf::Texture& lowGradeTexture, const sf::Texture& highGradeTexture) : Tile(size, position){
    this->init();
    this->initTextures(gridTexture,lowGradeTexture,highGradeTexture);
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

    if(this->mouseHoverTime != 0){
        switch(this->data.grade){
        case 0:
            this->data.grade = 6;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(205,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 1:
            this->data.grade = 0;
            this->gradeVisible = false;
            break;
        case 2:
            this->data.grade = 1;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 3:
            this->data.grade = 2;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(41,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 4:
            this->data.grade = 3;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(82,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 5:
            this->data.grade = 4;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(123,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 6:
            this->data.grade = 5;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(164,0), sf::Vector2i(39,25)));
            this->gradeVisible = true;
            break;
        }
    }
}
void GradeTile::mouseWheelMovedDown(const sf::Vector2f& mousePos){
    // if is on grade part
    if(this->mouseHoverTime != 0){
        switch(this->data.grade){
        case 0:
            this->data.grade = 1;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 1:
            this->data.grade = 2;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(41,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 2:
            this->data.grade = 3;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(82,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 3:
            this->data.grade = 4;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(123,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 4:
            this->data.grade = 5;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(164,0), sf::Vector2i(39,25)));
            this->gradeVisible = true;
            break;
        case 5:
            this->data.grade = 6;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i(205,0), sf::Vector2i(40,25)));
            this->gradeVisible = true;
            break;
        case 6:
            this->data.grade = 0;
            this->gradeVisible = false;
            break;
        }
    }
}

void GradeTile::update(){

}

void GradeTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
    window->draw(this->grid);
    window->draw(this->grade);
}
