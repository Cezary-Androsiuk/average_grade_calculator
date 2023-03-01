#include "Program.hpp"

void Program::loadTextures(){
    if(!this->gridTexture.loadFromFile("textures/tile_background.bmp")){
        printf("can't load texture in path \"textures/tile_background.bmp\"\n");
        this->exitApp();
    }
    this->gridTexture.setSmooth(false);
    this->gridTexture.setRepeated(false);


    if(!this->highGradeTexture.loadFromFile("textures/grades_test.bmp")){
        printf("can't load texture in path \"textures/grades.bmp\"\n");
        this->exitApp();
    }
    this->highGradeTexture.setSmooth(false);
    this->highGradeTexture.setRepeated(false);
}

void Program::initData(){
    std::fstream file;
    file.open("data.txt", std::ios::in);
    if(!file.good()){
        printf("File data.txt was not found!\n");
        this->exitApp();
    }
    std::string line;
    while(getline(file,line)){
        std::vector<std::string> line_of_data;
        std::istringstream sentence(line);
        std::string word;
        while(getline(sentence,word,';'))
            line_of_data.push_back(word);
        this->data.push_back(line_of_data);
    }
    file.close();
}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(WINDOW_POS_X/2,WINDOW_POS_Y/2));
    this->window->setFramerateLimit(FPS);
}

void Program::initShapes(){
    for(int i=0; i<this->data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            if(data[i][j][0] == '-' || data[i][j][0] == '+')
                this->tiles.push_back(new GradeTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + i,100.f + TILE_SIZE.y * j + j), data[i][j], this->gridTexture, this->highGradeTexture));
            else
                this->tiles.push_back(new TextTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + i,100.f + TILE_SIZE.y * j + j)));
        }
    }
}

void Program::exitApp(){
    this->window->close();
}

void Program::delShapes(){
    while(!this->tiles.empty()){
        delete this->tiles.back();
        this->tiles.pop_back();
    }
}


Program::Program(){
    this->initData();
    this->initWindow();
    this->loadTextures();
    this->initShapes();
}

Program::~Program(){
    this->delShapes();
    delete this->window;
    printf("Application closed correctly!\n");
}

void Program::pollEvent(){
    while(this->window->pollEvent(this->currentEvent)){
        switch (this->currentEvent.type){
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->currentEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            for(Tile* t : this->tiles){
                if(this->currentEvent.mouseButton.button == sf::Mouse::Left)
                    t->mouseLeftPressed();
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Right)
                    t->mouseRightPressed();
                else if(this->currentEvent.mouseButton.button == sf::Mouse::Middle)
                    t->mouseMiddlePressed();
            }
            break;
        case sf::Event::MouseWheelMoved:
            for(Tile* t : this->tiles){
                if(this->currentEvent.mouseWheel.delta == 1)
                    t->mouseWheelMovedUp();
                else
                    t->mouseWheelMovedDown();
            }
            break;
        default:
            break;
        }
    }
}

void Program::mouseHoverDetection(){
    for(Tile* t : this->tiles){
        t->mouseHoverInfo(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
    }
}

void Program::update(){
    this->pollEvent();

    this->mouseHoverDetection();
    for(Tile* t : this->tiles)
        t->getData();
}

void Program::render(){
    this->window->clear(sf::Color(240,240,240));

    for(Tile* t : this->tiles)
        t->render(this->window);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
