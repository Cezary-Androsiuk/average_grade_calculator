#include "GradeTile.hpp"

void GradeTile::init(){
    this->tileType = 1;
    this->data.enabled = 0;
    for(int i=0; i<5; i++)
        this->data.expectedGrade[i] = false;
    this->data.grade = 0;
    this->gradeVisible = false;
    this->mouseHoverTime = 0;
}

void GradeTile::interpretData(const std::string& rawData){

}

void GradeTile::initTextures(const sf::Texture& gridTexture, const sf::Texture& lowGradeTexture, const sf::Texture& highGradeTexture){
    this->grid.setTexture(gridTexture);

    this->grade.setTexture(highGradeTexture);
}

void GradeTile::initShapes(){
    this->mainShape.setFillColor(sf::Color(180,180,180));
    
    this->grid.setPosition(this->mainShape.getPosition());
    this->grid.setScale(sf::Vector2f(2.f, 2.f));

    this->grade.setPosition(sf::Vector2f(this->mainShape.getPosition().x + 10.f, this->mainShape.getPosition().y + 20.f));
    this->grade.setScale(sf::Vector2f(2.f, 2.f));
    this->grade.setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(40,25)));

    this->expectedGrades[0].setPosition(sf::Vector2f(AREA_EXPECTED_GRADE_3__FR.left + this->mainShape.getPosition().x, 
        AREA_EXPECTED_GRADE_3__FR.top + this->mainShape.getPosition().y));
    this->expectedGrades[0].setSize(sf::Vector2f(AREA_EXPECTED_GRADE_3__FR.width, AREA_EXPECTED_GRADE_3__FR.height));

    this->expectedGrades[1].setPosition(sf::Vector2f(AREA_EXPECTED_GRADE_35_FR.left + this->mainShape.getPosition().x, 
        AREA_EXPECTED_GRADE_35_FR.top + this->mainShape.getPosition().y));
    this->expectedGrades[1].setSize(sf::Vector2f(AREA_EXPECTED_GRADE_35_FR.width, AREA_EXPECTED_GRADE_35_FR.height));

    this->expectedGrades[2].setPosition(sf::Vector2f(AREA_EXPECTED_GRADE_4__FR.left + this->mainShape.getPosition().x, 
        AREA_EXPECTED_GRADE_4__FR.top + this->mainShape.getPosition().y));
    this->expectedGrades[2].setSize(sf::Vector2f(AREA_EXPECTED_GRADE_4__FR.width, AREA_EXPECTED_GRADE_4__FR.height));

    this->expectedGrades[3].setPosition(sf::Vector2f(AREA_EXPECTED_GRADE_45_FR.left + this->mainShape.getPosition().x, 
        AREA_EXPECTED_GRADE_45_FR.top + this->mainShape.getPosition().y));
    this->expectedGrades[3].setSize(sf::Vector2f(AREA_EXPECTED_GRADE_45_FR.width, AREA_EXPECTED_GRADE_45_FR.height));

    this->expectedGrades[4].setPosition(sf::Vector2f(AREA_EXPECTED_GRADE_5__FR.left + this->mainShape.getPosition().x, 
        AREA_EXPECTED_GRADE_5__FR.top + this->mainShape.getPosition().y));
    this->expectedGrades[4].setSize(sf::Vector2f(AREA_EXPECTED_GRADE_5__FR.width, AREA_EXPECTED_GRADE_5__FR.height));

    for(int i=0; i<5; i++)
        this->expectedGrades[i].setFillColor(sf::Color(220,80,80));
}

GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Texture& gridTexture, const sf::Texture& lowGradeTexture, const sf::Texture& highGradeTexture) : Tile(size, position){
    this->init();
    this->interpretData(rawData);
    this->initTextures(gridTexture,lowGradeTexture,highGradeTexture);
    this->initShapes();
}

GradeTile::~GradeTile(){

}


void GradeTile::mouseLeftPressed(){
    switch (this->mouseHoverType){
    case 0:
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        this->data.expectedGrade[this->mouseHoverType-1] = (this->data.expectedGrade[this->mouseHoverType-1] ? false : true);
        break;
    
    case 6:
        printf("grade tile left\n");
        break;
    }
}
void GradeTile::mouseRightPressed(){
    // lock
    switch (this->mouseHoverType){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    
    case 6:
        printf("grade tile right\n");
        break;
    }
}
void GradeTile::mouseMiddlePressed(){

}
void GradeTile::mouseWheelMovedUp(){
    // if is on grade part

    if(this->mouseHoverType == 6){
        if(this->data.grade < 1) this->data.grade = 6;
        else this->data.grade--;

        if(this->data.grade == 0) this->gradeVisible = false;
        else{
            this->gradeVisible = true;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i((this->data.grade - 1)*41,0), sf::Vector2i(40,25)));
        }
    }
}
void GradeTile::mouseWheelMovedDown(){
    // if is on grade part
    if(this->mouseHoverType == 6){
        if(this->data.grade > 5) this->data.grade = 0;
        else this->data.grade++;

        if(this->data.grade == 0) this->gradeVisible = false;
        else{
            this->gradeVisible = true;
            this->grade.setTextureRect(sf::IntRect(sf::Vector2i((this->data.grade - 1)*41,0), sf::Vector2i(40,25)));
        }
    }
}

void GradeTile::update(){

}

void GradeTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
    for(int i=0; i<5; i++)
        if(this->data.expectedGrade[i])
            window->draw(this->expectedGrades[i]);
    window->draw(this->grid);
    if(this->gradeVisible)
        window->draw(this->grade);
}


void GradeTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos)){
        this->mouseHoverTime++;
        // detect above what part mouse is hovering
        if(AREA_EXPECTED_GRADE_3__FR.contains(this->objectRelativePosition(mousePos)))
            this->mouseHoverType = 1;
        else if(AREA_EXPECTED_GRADE_35_FR.contains(this->objectRelativePosition(mousePos)))
            this->mouseHoverType = 2;
        else if(AREA_EXPECTED_GRADE_4__FR.contains(this->objectRelativePosition(mousePos)))
            this->mouseHoverType = 3;
        else if(AREA_EXPECTED_GRADE_45_FR.contains(this->objectRelativePosition(mousePos)))
            this->mouseHoverType = 4;
        else if(AREA_EXPECTED_GRADE_5__FR.contains(this->objectRelativePosition(mousePos)))
            this->mouseHoverType = 5;
        else if(AREA_GRADE_FR.contains(this->objectRelativePosition(mousePos)))
            this->mouseHoverType = 6;
    }
    else {
        this->mouseHoverTime = 0;
        this->mouseHoverType = 0;
    }
}