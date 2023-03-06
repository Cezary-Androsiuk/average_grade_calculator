#include "GradeTile.hpp"

void GradeTile::init(){
    this->tileType = 1;

    this->data.enabled = true;
    this->data.locked = false;
    for(int i=0; i<5; i++)
        this->data.expectedGrade[i] = false;
    this->data.grade = 0;
    this->data.grade_type = 0;
    
    this->mouseHoverOnPart = 0;
    this->mouseHoverTime = 0;
}
void GradeTile::interpretData(const std::string& rawData){
    // "10[00000]g0"
    // enabled locked [expected grade] grade_type grade
    switch (rawData[0]){
    case '1': this->data.enabled = true;
        break;
    case '0': this->data.enabled = false;
        break;
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[0],rawData.c_str());
        break;
    }
    switch (rawData[1]){
    case '1': this->data.locked = true;
        break;
    case '0': this->data.locked = false;
        break;
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[1],rawData.c_str());
        break;
    }
    // rawData[2] == '['
    for(int i=0; i<5; i++){
        switch (rawData[i+3]){
        case '0': this->data.expectedGrade[i] = false;
            break;
        case '1': this->data.expectedGrade[i] = true;
            break;
        default: printf("can not interpret '%c' in \"%s\"\n",rawData[i+3],rawData.c_str());
            break;
        }
    }
    // rawData[8] == ']'

    switch (rawData[9]){
    case 'g': this->data.grade_type = 1;
        break;
    case 'r': this->data.grade_type = 2;
        break;
    
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[9],rawData.c_str());
        break;
    }


    switch (rawData[10]){
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': this->data.grade = rawData[10]-48;
        break;
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[10],rawData.c_str());
        break;
    }
}
void GradeTile::initTextures(const sf::Texture& gridTexture, const sf::Texture& highGradeTexture){
    this->grid.setTexture(gridTexture);

    this->grade.setTexture(highGradeTexture);
}
void GradeTile::initShapes(){
    this->mainShape.setFillColor(sf::Color(175,175,175));
    
    this->grid.setPosition(this->tilePosition);

    this->grade.setPosition(sf::Vector2f(this->tilePosition.x + 21.f, this->tilePosition.y + 44.f));
    this->updateGradeTexture();

    for(int i=0; i<5; i++){
        this->expectedGrades[i].setPosition(
            sf::Vector2f(
                this->mouseUpdateAreaOnTile[i].left + this->tilePosition.x,
                this->mouseUpdateAreaOnTile[i].top + this->tilePosition.y
            )
        );
        this->expectedGrades[i].setSize(
            sf::Vector2f(
                this->mouseUpdateAreaOnTile[i].width,
                this->mouseUpdateAreaOnTile[i].height
            )
        );
        this->expectedGrades[i].setFillColor(sf::Color(225,65,65));
    }
}


GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Texture& gridTexture, const sf::Texture& highGradeTexture) : Tile(size, position){
    this->init();
    this->interpretData(rawData);
    this->initTextures(gridTexture,highGradeTexture);
    this->initShapes();
}
GradeTile::~GradeTile(){

}


void GradeTile::updateGradeTexture(){
    this->grade.setTextureRect(sf::IntRect(sf::Vector2i(this->data.grade*80,0), sf::Vector2i(80,50)));
}

void GradeTile::mouseLeftPressed(){
    if(this->data.enabled == false)
        return;

    switch (this->mouseHoverOnPart){
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        this->data.expectedGrade[this->mouseHoverOnPart-1] = (this->data.expectedGrade[this->mouseHoverOnPart-1] ? false : true);
        break;
    
    case 6:
        printf("grade tile left\n");
        break;
    }
}
void GradeTile::mouseRightPressed(){
    // enable/disable
    switch (this->mouseHoverOnPart){
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        this->data.enabled = (this->data.enabled ? false : true);
        break;
    }
}
void GradeTile::mouseMiddlePressed(){
    // lock/unlock
}
void GradeTile::mouseWheelMovedUp(){
    if(this->data.enabled == false)
        return;

    if(this->mouseHoverOnPart == 6){
        if(this->data.grade > 8) this->data.grade = 0;
        else this->data.grade++;

        this->updateGradeTexture();
    }
}
void GradeTile::mouseWheelMovedDown(){
    if(this->data.enabled == false)
        return;
        
    if(this->mouseHoverOnPart == 6){
        if(this->data.grade < 1) this->data.grade = 9;
        else this->data.grade--;

        this->updateGradeTexture();
    }
}


void GradeTile::update(){
 
}
void GradeTile::render(sf::RenderTarget* window){
    if(this->data.enabled){
        window->draw(this->mainShape);
        for(int i=0; i<5; i++)
            if(this->data.expectedGrade[i])
                window->draw(this->expectedGrades[i]);
        window->draw(this->grid);
        window->draw(this->grade);
    }
}


std::string GradeTile::getData() const{
    // "10[00000]g0"
    // enabled locked [expected grade] grade_type grade
    std::string dataToReturn = "";
    dataToReturn += (this->data.enabled ? '1' : '0');
    dataToReturn += (this->data.locked ? '1' : '0');
    
    dataToReturn += '[';
    for(int i=0; i<5; i++) dataToReturn += (this->data.expectedGrade[i] ? '1' : '0');
    dataToReturn += ']';

    switch (this->data.grade_type){
    case 1: dataToReturn += 'g';
        break;
    case 2: dataToReturn += 'r';
        break;
    default:
        break;
    }
    dataToReturn += this->data.grade + 48;
    return dataToReturn;
}
void GradeTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos)){
        this->mouseHoverTime++;
        // detect above what part mouse is hovering (nice inglisz)
        for(int i=0; i<6; i++)
            if(this->mouseUpdateAreaOnTile[i].contains(this->globalPosition_to_localPosition(mousePos)))
                this->mouseHoverOnPart = i+1;
    }
    else {
        this->mouseHoverTime = 0;
        this->mouseHoverOnPart = 0;
    }
}