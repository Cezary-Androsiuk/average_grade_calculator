#include "GradeTile.hpp"

void GradeTile::init(){
    this->tileType = 0;

    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect( 1.f, 0.f, 24.f, 18.f)); // expected grade 3
    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect(25.f, 0.f, 24.f, 18.f)); // expected grade 3.5
    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect(49.f, 0.f, 24.f, 18.f)); // expected grade 4
    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect(73.f, 0.f, 24.f, 18.f)); // expected grade 4.5
    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect(97.f, 0.f, 24.f, 18.f)); // expected grade 5
    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect(96.f, 96.f, 26.f, 26.f)); // lock 
    this->mouseActionsAreasOnTile.push_back(new const sf::FloatRect(0.f, 18.f, 122.f, 104.f)); // current grade


#if DRAW_MOUSE_ACTIONS_AREAS_ON_TILE == 1
    for(const sf::FloatRect* cfr : this->mouseActionsAreasOnTile){
        sf::RectangleShape* rs = new sf::RectangleShape();
        rs->setSize(sf::Vector2f(cfr->width, cfr->height));
        rs->setPosition(this->localPosition_to_globalPosition(sf::Vector2f(cfr->left, cfr->top)));
        rs->setFillColor(sf::Color(rand()%255, rand()%255, rand()%255, 100));
        this->mouseActionsAreasOnTile_asRectangle.push_back(rs);
    }
#endif

    this->data.enabled = true;
    this->data.locked = false;
    for(int i=0; i<5; i++)
        this->data.expectedGrade[i] = false;
    this->data.grade = 0;
    this->data.grade2 = false;
    this->data.grade_type = 1;

    
    this->mouseHoverOnPart = 0;
    this->mouseHoverTime = 0;
}
void GradeTile::interpretData(const std::string& rawData){
    // "10[00000]000"
    // enabled locked [expected grade] grade_type grade2 grade
    switch (rawData[0]){
    case '1': this->data.enabled = true; break;
    case '0': this->data.enabled = false; break;
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[0],rawData.c_str());
        break;
    }

    switch (rawData[1]){
    case '1': this->data.locked = true; break;
    case '0': this->data.locked = false; break;
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[1],rawData.c_str());
        break;
    }

    // rawData[2] == '['
    for(int i=0; i<5; i++){
        switch (rawData[i+3]){
        case '0': this->data.expectedGrade[i] = false; break;
        case '1': this->data.expectedGrade[i] = true; break;
        default: printf("can not interpret '%c' in \"%s\"\n",rawData[i+3],rawData.c_str());
            break;
        }
    }
    // rawData[8] == ']'

    if('0' <= rawData[9] && rawData[9] <= (MAX_GRADE_TYPE + 48)) this->data.grade_type = rawData[9] - 48; // less than 10
    else printf("can not interpret '%c' in \"%s\"\n",rawData[9],rawData.c_str());

    switch (rawData[10]){
    case '1': this->data.grade2 = true; break;
    case '0': this->data.grade2 = false; break;
    default: printf("can not interpret '%c' in \"%s\"\n",rawData[10],rawData.c_str());
        break;
    }

    if('0' <= rawData[11] && rawData[11] <= '6') this->data.grade = rawData[11] - 48; // less than 10
    else printf("can not interpret '%c' in \"%s\"\n",rawData[11],rawData.c_str());
}
void GradeTile::initTextures(const sf::Texture& tileTemplateTexture, const sf::Texture& expectedGradeTexture, const sf::Texture& currentGradeTexture){
    this->tileTemplate.setTexture(tileTemplateTexture);
    for(int i=0; i<5; i++) this->expectedGrade[i].setTexture(expectedGradeTexture);
    this->currentGrade.setTexture(currentGradeTexture);
}
void GradeTile::initShapes(){
    this->mainShape.setFillColor(sf::Color(0,0,0));
    
    this->tileTemplate.setPosition(this->localPosition_to_globalPosition(sf::Vector2f(0.f, 0.f)));
    this->updateTileTemplateTexture();


    for(int i=0; i<5; i++)
        this->expectedGrade[i].setPosition(this->localPosition_to_globalPosition(sf::Vector2f(this->mouseActionsAreasOnTile[i]->left + 1.f, 2.f)));
    this->updateExpectedGradeTexture();


    this->currentGrade.setPosition(this->localPosition_to_globalPosition(sf::Vector2f(this->mouseActionsAreasOnTile[6]->left,this->mouseActionsAreasOnTile[6]->top)));
    this->updateCurrentGradeTexture();
}


GradeTile::GradeTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Texture& tileTemplateTexture, 
const sf::Texture& expectedGradeTexture, const sf::Texture& currentGradeTexture) : Tile(size, position){
    this->init();
    this->interpretData(rawData);
    this->initTextures(tileTemplateTexture, expectedGradeTexture, currentGradeTexture);
    this->initShapes();
}
GradeTile::~GradeTile(){
    for(const sf::FloatRect* cfr : this->mouseActionsAreasOnTile)
        delete cfr;

#if DRAW_MOUSE_ACTIONS_AREAS_ON_TILE == 1
    for(sf::RectangleShape* rs : this->mouseActionsAreasOnTile_asRectangle)
        delete rs;
#endif
}


void GradeTile::updateTileTemplateTexture(){
    this->tileTemplate.setTextureRect(
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
                sf::Vector2i(22*i, this->data.expectedGrade[i] * 14),
                sf::Vector2i(22, 14)
        )
    );
}

void GradeTile::updateCurrentGradeTexture(){
    this->currentGrade.setTextureRect(
        sf::IntRect(
            sf::Vector2i(this->data.grade * 122 + this->data.grade2 * 854, this->data.grade_type * 104), 
            sf::Vector2i(122, 104)
        )
    );
}

void GradeTile::mouseLeftPressed(){
    if(!this->data.enabled)
        return;

    if(1 <= this->mouseHoverOnPart && this->mouseHoverOnPart <= 5 && !this->data.locked){
        this->data.expectedGrade[this->mouseHoverOnPart-1] = (this->data.expectedGrade[this->mouseHoverOnPart-1] ? false : true);
        this->updateExpectedGradeTexture();
    }
    else if(this->mouseHoverOnPart == 6){
        this->data.locked = (this->data.locked ? false : true);
        this->updateTileTemplateTexture();
    }
    else if(this->mouseHoverOnPart == 7 && !this->data.locked){
        if(this->data.grade_type >= MAX_GRADE_TYPE)
            this->data.grade_type = 0;
        else
            this->data.grade_type++;
        this->updateCurrentGradeTexture();
    }
}
void GradeTile::mouseRightPressed(){
    if(!this->data.enabled || this->data.locked)
        return;
    
    if(this->mouseHoverOnPart == 7)
        this->data.grade2 = (this->data.grade2 ? false : true);
    this->updateCurrentGradeTexture();
}
void GradeTile::mouseMiddlePressed(){
    if(this->mouseHoverOnPart != 0)
        this->data.enabled = (this->data.enabled ? false : true);
}

void GradeTile::mouseWheelMovedUp(){
    if(!this->data.enabled || this->data.locked)
        return;

    if(this->mouseHoverOnPart >= 6){
        if(this->data.grade > 5) this->data.grade = 0;
        else this->data.grade++;

        this->updateCurrentGradeTexture();
    }
}
void GradeTile::mouseWheelMovedDown(){
    if(!this->data.enabled || this->data.locked)
        return;
        
    if(this->mouseHoverOnPart >= 6){
        if(this->data.grade < 1) this->data.grade = 6;
        else this->data.grade--;

        this->updateCurrentGradeTexture();
    }
}


void GradeTile::update(){
 
}
void GradeTile::render(sf::RenderTarget* window){
    if(this->data.enabled){
        // window->draw(this->mainShape);
        window->draw(this->tileTemplate);
        for(int i=0; i<5; i++)
            window->draw(this->expectedGrade[i]);
        window->draw(this->currentGrade);

    #if DRAW_MOUSE_ACTIONS_AREAS_ON_TILE == 1
        for(sf::RectangleShape* rs : this->mouseActionsAreasOnTile_asRectangle)
            window->draw(*rs);
    #endif
    }
}


std::string GradeTile::getData() const{
    // "10[00000]000"
    // enabled locked [expected grade] grade_type grade2 grade
    std::string dataToReturn = "";
    dataToReturn += (this->data.enabled ? '1' : '0');
    dataToReturn += (this->data.locked ? '1' : '0');
    
    dataToReturn += '[';
    for(int i=0; i<5; i++) dataToReturn += (this->data.expectedGrade[i] ? '1' : '0');
    dataToReturn += ']';

    dataToReturn += this->data.grade_type + 48; // less than 10
    dataToReturn += this->data.grade2 + 48;
    dataToReturn += this->data.grade + 48; // less than 10
    return dataToReturn;
}
void GradeTile::mouseHoverUpdate(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos)){
        this->mouseHoverTime++;
        // detect above what part mouse is hovering (nice inglisz)
        int i = 1;
        for(const sf::FloatRect* cfr : this->mouseActionsAreasOnTile){
            if(cfr->contains(this->globalPosition_to_localPosition(mousePos))){
                this->mouseHoverOnPart = i;
                break;
            }
            i++;
        }
    }
    else {
        this->mouseHoverTime = 0;
        this->mouseHoverOnPart = 0;
    }
}