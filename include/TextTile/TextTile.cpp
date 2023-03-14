#include "TextTile.hpp"

void TextTile::init(){
    this->tileType = 2;
    this->charSize = 0;
}
void TextTile::interpretData(const std::string& rawData){
    std::string chS = rawData;
    chS = chS.substr(chS.find('(')+1);
    chS.erase(chS.end()-1);
    this->charSize = atoi(chS.c_str());
    
    this->data = rawData;
    this->data.erase(this->data.find('('), this->data.back());
}
void TextTile::initText(const sf::Font& font, const unsigned int& charSize){
    if(this->charSize == 0)
        this->charSize = charSize;
    std::string tmp;
    for(char i : this->data){
        if(i != ' ')
            tmp += i;
        else{
            this->text_vector.push_back(new sf::Text(tmp, font, this->charSize));
                                                                            this->text_vector_globalBounds.push_back(new sf::RectangleShape());
            tmp.clear();
        }
    }
    this->text_vector.push_back(new sf::Text(tmp, font, this->charSize));
                                                                            this->text_vector_globalBounds.push_back(new sf::RectangleShape());
    
    for(sf::Text* t : this->text_vector)
        t->setFillColor(sf::Color(30,200,30));
        
    
                                                                            for(sf::RectangleShape* t : this->text_vector_globalBounds)
                                                                                t->setFillColor(sf::Color(255,65,65));


    // for(int i=0; i<this->text_vector.size(); i++){
    //     sf::FloatRect fr = text_vector[i]->getGlobalBounds();
    //     this->text_vector_globalBounds[i]->setOrigin(
    //         fr.left + fr.width/2.f,
    //         fr.top + fr.height/2.f
    //     );
    // }



    this->updateTextPosition();

}
void TextTile::initShape(){
    this->mainShape.setFillColor(sf::Color(20,20,20));

}


TextTile::TextTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Font& font, const unsigned int& charSize) : Tile(size,position){
    this->init();
    this->interpretData(rawData);
    this->initText(font, charSize);
    this->initShape();
}
TextTile::~TextTile(){
    for(sf::Text* t : this->text_vector)
        delete t;
}

void TextTile::updateTextPosition(){
    for(sf::Text* i : this->text_vector){
        std::string a = "0";
        a[0] = rand()%50 + 40;
        i->setString(a);
        i->rotate(9.f);
    }

    for(int i=0; i<this->text_vector.size(); i++){
        this->text_vector[i]->setCharacterSize(this->charSize);
        this->text_vector[i]->setPosition(sf::Vector2f(
            this->mainShape.getGlobalBounds().left + (this->mainShape.getGlobalBounds().width - this->text_vector[i]->getGlobalBounds().width)/2,
            this->mainShape.getGlobalBounds().top + this->charSize * i + 2.f
        ));
                                                                            this->text_vector_globalBounds[i]->setPosition(this->text_vector[i]->getPosition());
                                                                            this->text_vector_globalBounds[i]->setSize(sf::Vector2f(
                                                                                    this->text_vector[i]->getLocalBounds().width,
                                                                                    this->text_vector[i]->getLocalBounds().height
                                                                            ));
    }
    
}

void TextTile::mouseLeftPressed(){

}
void TextTile::mouseRightPressed(){

}
void TextTile::mouseMiddlePressed(){
    
}
void TextTile::mouseWheelMovedUp(){
    if(this->mouseHoverTime){
        if(this->charSize < 100)
            this->charSize++;
        this->updateTextPosition();
        printf("current text char Size: %d\n", this->charSize);
    }
}
void TextTile::mouseWheelMovedDown(){
    if(mouseHoverTime){
        if(this->charSize > 1)
            this->charSize--;
        this->updateTextPosition();
        printf("current text char Size: %d\n", this->charSize);
    }
}
void TextTile::keyboardKeys(const sf::Keyboard::Key&){

}


void TextTile::update(){
    
}
void TextTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
                                                                            for(sf::RectangleShape* t : this->text_vector_globalBounds)
                                                                                window->draw(*t);
    for(sf::Text* t : this->text_vector)
        window->draw(*t);
}


std::string TextTile::getData() const{
    return this->data + '(' + std::to_string(this->charSize) + ')';
}
void TextTile::mouseHoverUpdate(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos))
        this->mouseHoverTime++;
    else 
        this->mouseHoverTime = 0;
}