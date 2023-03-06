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
void GradeTile::initTextures(const sf::Texture& gridTexture, const sf::Texture& expectedGradeTexture, const sf::Texture& currentGradeTexture){
    this->grid.setTexture(gridTexture);
    for(int i=0; i<5; i++) this->expectedGrade[i].setTexture(expectedGradeTexture);
    this->currentGrade.setTexture(currentGradeTexture);
}
void GradeTile::initShapes(){
    this->mainShape.setFillColor(sf::Color(175,175,175));
    
    this->grid.setPosition(this->tilePosition);
    this->updateGridTexture();

    for(int i=0; i<5; i++){
        this->expectedGrade[i].setPosition(
            sf::Vector2f(
                this->mouseUpdateAreaOnTile[i].left + this->tilePosition.x + 1,
                this->mouseUpdateAreaOnTile[i].top + this->tilePosition.y + 1
            )
        );
    }
    this->updateExpectedGradeTexture();

    this->currentGrade.setPosition(sf::Vector2f(this->tilePosition.x + 21.f, this->tilePosition.y + 44.f));
    this->updateCurrentGradeTexture();
}


GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Texture& gridTexture, const sf::Texture& expectedGradeTexture, const sf::Texture& currentGradeTexture) : Tile(size, position){
    this->init();
    this->interpretData(rawData);
    this->initTextures(gridTexture, expectedGradeTexture, currentGradeTexture);
    this->initShapes();
}
GradeTile::~GradeTile(){

}


void GradeTile::updateGridTexture(){
    this->grid.setTextureRect(
        sf::IntRect(
            sf::Vector2i(this->data.locked*122, 0), 
            sf::Vector2i(122, 122)
            )
        );
}

void GradeTile::updateExpectedGradeTexture(){
    for(int i=0; i<5; i++)
        this->expectedGrade[i].setTextureRect(
            sf::IntRect(
                sf::Vector2i(22.f*i, 0.f),
                sf::Vector2i(22.f, 14.f)
            )
        );
}

void GradeTile::updateCurrentGradeTexture(){
    this->currentGrade.setTextureRect(
        sf::IntRect(
            sf::Vector2i(this->data.grade*80, 0), 
            sf::Vector2i(80, 50)
            )
        );
}

void GradeTile::mouseLeftPressed(){
    if(!this->data.enabled || this->data.locked)
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
    if(!this->data.enabled)
        return;
    // lock/unlock
    switch (this->mouseHoverOnPart){
    case 1: break;
    case 2: break;
    case 3: break;
    case 4: break;
    case 5: break;
    case 6:
        this->data.locked = (this->data.locked ? false : true);
        this->updateGridTexture();
        break;
    }
}
void GradeTile::mouseMiddlePressed(){
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
void GradeTile::mouseWheelMovedUp(){
    if(!this->data.enabled || this->data.locked)
        return;

    if(this->mouseHoverOnPart == 6){
        if(this->data.grade > 8) this->data.grade = 0;
        else this->data.grade++;

        this->updateCurrentGradeTexture();
    }
}
void GradeTile::mouseWheelMovedDown(){
    if(!this->data.enabled || this->data.locked)
        return;
        
    if(this->mouseHoverOnPart == 6){
        if(this->data.grade < 1) this->data.grade = 9;
        else this->data.grade--;

        this->updateCurrentGradeTexture();
    }
}


void GradeTile::update(){
 
}
void GradeTile::render(sf::RenderTarget* window){
    if(this->data.enabled){
        // window->draw(this->mainShape);
        window->draw(this->grid);
        for(int i=0; i<5; i++)
            if(this->data.expectedGrade[i])
                window->draw(this->expectedGrade[i]);
        window->draw(this->currentGrade);
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