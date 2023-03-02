#include "Program.hpp"

void Program::loadSources(){
    if(!this->gridTexture.loadFromFile("sources/tile_background.bmp")){
        printf("can't load texture in path sources/tile_background.bmp\n");
        this->exitApp();
    }
    this->gridTexture.setSmooth(false);
    this->gridTexture.setRepeated(false);


    if(!this->highGradeTexture.loadFromFile("sources/grades_test.bmp")){
        printf("can't load texture in path sources/grades.bmp\n");
        this->exitApp();
    }
    this->highGradeTexture.setSmooth(false);
    this->highGradeTexture.setRepeated(false);

    if(!this->font.loadFromFile("sources/OpenSans-Light.ttf")){
        printf("can't load font in path sources/OpenSans-Light.ttf");
        this->exitApp();
    }
}

void Program::initData(){
    std::vector<std::vector<std::string>> vdata;
    std::fstream file;
    file.open(DATA_FILE, std::ios::in);
    if(!file.good()){
        printf("can't read file %s!\n",DATA_FILE);
        this->exitApp();
    }
    std::string line;
    while(getline(file,line)){
        std::vector<std::string> line_of_data;
        std::istringstream sentence(line);
        std::string word;
        while(getline(sentence,word,';'))
            line_of_data.push_back(word);
        vdata.push_back(line_of_data);
    }
    file.close();

    int expectedLength = vdata[0].size();
    for(int i=0; i<vdata.size(); i++){
        if(vdata[0].size() != expectedLength){
            printf("inconsistency in data lines length!\n");
            this->exitApp();
        }
    }

    this->rows = vdata.size();
    this->lines = vdata[0].size();
    this->data = new std::string*[this->rows];
    for(int i=0; i<this->rows; i++)
        this->data[i] = new std::string[this->lines];

    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->data[i][j] = vdata[i][j];
        }
    }
    this->tiles = new Tile**[this->rows];
    for(int i=0; i<this->rows; i++)
        this->tiles[i] = new Tile*[this->lines];
}

void Program::initWindow(){
    //                left margin +   sum of tiles width     + sum of separators between tiles   + right margin
    unsigned int windowWidth = 10 + this->rows * TILE_SIZE.y +    (this->rows-1) * 2             + 10;
    //                   top margin +   sum of tiles heights    + sum of separators between tiles + bottom margin
    unsigned int windowHeight = 100 + this->lines * TILE_SIZE.x +    (this->lines-1) * 2          + 10;
    
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::Default);
    this->window->setPosition(sf::Vector2i((1920 - windowWidth)/2,(1080 - windowHeight)/2));
    this->window->setFramerateLimit(FPS);
}

void Program::initShapes(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){

            if(this->data[i][j][0] == '-' || this->data[i][j][0] == '+')
                this->tiles[i][j] = new GradeTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + 2*i,100.f + TILE_SIZE.y*j + 2*j), this->data[i][j], this->gridTexture, this->highGradeTexture);
            else
                this->tiles[i][j] = new TextTile(TILE_SIZE,sf::Vector2f(10.f + TILE_SIZE.x*i + 2*i,100.f + TILE_SIZE.y*j + 2*j), this->data[i][j], this->font);
        }
    }

    this->gradeAvarageName.setFont(this->font);
    this->gradeAvarageRange.setFont(this->font);
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

void Program::saveData(){
    // save to file
    std::fstream file;
    file.open(DATA_FILE, std::ios::out);
    if(!file.good()){
        printf("can't save data to %s!\n",DATA_FILE);
        this->deleteData();
        return;
    }

    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            file << this->data[i][j] << ";";
        }
        file << "\n";
    }
    file.close();

    this->deleteData();
}

void Program::deleteData(){
    for(int i=0; i<this->rows; i++)
        delete [] this->data[i];
    delete [] this->data;
}

Program::Program(){
    this->initData();
    this->initWindow();
    this->loadSources();
    this->initShapes();
}

Program::~Program(){
    this->delShapes();
    this->saveData();
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

bool Program::getGradeFromSingleData(const std::string& singleData, float& min, float& max) const{
    // "+00000r0"
    //  01234567

    if(singleData[7] != '0'){
        // known grade
        float grade;
        switch(singleData[7]){
            case '1': 
                grade = 2.f;
                break;
            case '2': 
                grade = 2.5f;
                break;
            case '3': 
                grade = 2.75f;
                break;
            case '4': 
                grade = 3.f;
                break;
            case '5': 
                grade = 3.25f;
                break;
            case '6': 
                grade = 3.5f;
                break;
            case '7': 
                grade = 4.f;
                break;
            case '8': 
                grade = 4.5f;
                break;
            case '9':
                grade = 5.f;
                break;
        }
        min = grade;
        max = grade;
        return true;
    }
    else if(singleData.find("00000",1) != std::string::npos){
        // unknown grade and unknown range
        // this tiles are not used in avarage grade
        return false;    
    }
    // unknown grade but known range
    // XD
    min = 3.f;
    if(singleData[1] == '0'){
        min = 3.5f;
        if(singleData[2] == '0'){
            min = 4.f;
            if(singleData[3] == '0'){
                min = 4.5f;
                if(singleData[4] == '0'){
                    min = 5.f;
                }
            }
        }
    }
    max = 5.f;
    if(singleData[5] == '0'){
        max = 4.5f;
        if(singleData[4] == '0'){
            max = 4.f;
            if(singleData[3] == '0'){
                max = 3.5f;
                if(singleData[2] == '0'){
                    max = 3.f;
                }
            }
        }
    }

    return true;
}
float Program::computeGradeAvarage(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            if(this->data[i][j][0] == '+'){
                int gradesCount = 0;
                float min,max;
                float sumMin = 0.f, sumMax = 0.f;
                if(this->getGradeFromSingleData(data[i][j],min,max)){

                    gradesCount++;
                }
            }
        }
    }

}

void Program::update(){
    this->pollEvent();

    this->mouseHoverDetection();
    // update this->data depends on tiles data
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->data[i][j] = this->tiles[i][j]->getData();
        }
    }
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
