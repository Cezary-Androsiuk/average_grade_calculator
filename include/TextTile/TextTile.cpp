#include "TextTile.hpp"

void TextTile::init(){
    this->tileType = 2;
}
void TextTile::interpretData(const std::string& rawData){
    this->name = rawData;
}
void TextTile::initText(const sf::Font& font){
    this->text.setFont(font);
    this->text.setString(this->name);
    this->text.setCharacterSize(10);
    this->text.setPosition(this->tilePosition);
    this->text.setFillColor(sf::Color(0,0,0));
}
void TextTile::initShape(){
    this->mainShape.setFillColor(sf::Color(200,200,200));

}


TextTile::TextTile(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& rawData, const sf::Font& font) : Tile(size,position){
    this->init();
    this->interpretData(rawData);
    this->initText(font);
    this->initShape();
}
TextTile::~TextTile(){

}

std::vector<sf::Text> adjustTextInField(const sf::FloatRect& field, const sf::Text& orgtext){
    std::vector<sf::Text> text_vector;
    std::wstring wtext(orgtext.getString());
    std::wstring tmp;
    for(wchar_t i : wtext){
        if(i != L' ')
            tmp += i;
        else{
            text_vector.push_back(sf::Text(tmp, *orgtext.getFont(), orgtext.getCharacterSize()));
            tmp.clear();
        }
    }

    for(int i=0; i<text_vector.size(); i++){
        text_vector[i].setPosition(sf::Vector2f(
            field.left + (field.width - text_vector[i].getGlobalBounds().width)/2,
            field.top + orgtext.getCharacterSize() * i + 2.f
        ));
    }

    return text_vector;
}

void TextTile::mouseLeftPressed(){

}
void TextTile::mouseRightPressed(){

}
void TextTile::mouseMiddlePressed(){
    
}
void TextTile::mouseWheelMovedUp(){
    
}
void TextTile::mouseWheelMovedDown(){
    
}
void TextTile::keyboardKeys(const sf::Keyboard::Key&){

}


void TextTile::update(){

}
void TextTile::render(sf::RenderTarget* window){
    window->draw(this->mainShape);
    window->draw(this->text);
}


std::string TextTile::getData() const{
    return this->name;
}
void TextTile::mouseHoverInfo(const sf::Vector2f& mousePos){
    if(this->mainShape.getGlobalBounds().contains(mousePos))
        this->mouseHoverTime++;
    else 
        this->mouseHoverTime = 0;
}