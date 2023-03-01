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
        printf("can't read file data.txt!\n");
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

    int expectedLength = this->data[0].size();
    for(int i=0; i<this->data.size(); i++){
        if(data[0].size() != expectedLength){
            printf("inconsistency in data lines length!\n");
            this->exitApp();
        }
    }

    this->rows = this->data.size();
    this->lines = this->data[0].size();

    this->tiles = new Tile**[this->rows];
    for(int i=0; i<this->rows; i++)
        this->tiles[i] = new Tile*[this->lines];
}

void Program::initWindow(){
    //                   top margin +   sum of tiles heights    + sum of separators between tiles + bottom margin
    unsigned int windowHeight = 100 + this->lines * TILE_SIZE.x +    (this->lines-1) * 2          + 10;
    //                left margin +   sum of tiles heights   + sum of separators between tiles   + right margin
    unsigned int windowWidth = 10 + this->rows * TILE_SIZE.y +    (this->rows-1) * 2             + 10;
    
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(WINDOW_POS_X/2,WINDOW_POS_Y/2));
    this->window->setFramerateLimit(FPS);
}

void Program::initShapes(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){

            if(data[i][j][0] == '-' || data[i][j][0] == '+')
                this->tiles[i][j] = new GradeTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + 2*i,100.f + TILE_SIZE.y*j + 2*j), data[i][j], this->gridTexture, this->highGradeTexture);
            else
                this->tiles[i][j] = new TextTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + 2*i,100.f + TILE_SIZE.y*j + 2*j));
        }
    }
}

void Program::exitApp(){
    this->window->close();
}

void Program::delShapes(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            delete this->tiles[i][j];
        }
        delete [] this->tiles[i];
    }
    delete [] this->tiles;
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
            for(int i=0; i<this->rows; i++){
                for(int j=0; j<this->lines; j++){
                    if(this->currentEvent.mouseButton.button == sf::Mouse::Left)
                        this->tiles[i][j]->mouseLeftPressed();
                    else if(this->currentEvent.mouseButton.button == sf::Mouse::Right)
                        this->tiles[i][j]->mouseRightPressed();
                    else if(this->currentEvent.mouseButton.button == sf::Mouse::Middle)
                        this->tiles[i][j]->mouseMiddlePressed();    
                }
            }
            break;
        case sf::Event::MouseWheelMoved:
            for(int i=0; i<this->rows; i++){
                for(int j=0; j<this->lines; j++){
                if(this->currentEvent.mouseWheel.delta == 1)
                    this->tiles[i][j]->mouseWheelMovedUp();
                else
                    this->tiles[i][j]->mouseWheelMovedDown();
                }
            }
            break;
        default:
            break;
        }
    }
}

void Program::mouseHoverDetection(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->tiles[i][j]->mouseHoverInfo(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
        }
    }
}

void Program::update(){
    this->pollEvent();

    this->mouseHoverDetection();
    // for(Tile* t : this->tiles)
        // t->getData();
}

void Program::render(){
    this->window->clear(sf::Color(240,240,240));

    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->tiles[i][j]->render(this->window);
        }
    }

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
