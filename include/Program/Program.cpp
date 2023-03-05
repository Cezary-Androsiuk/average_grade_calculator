#include "Program.hpp"

void Program::loadSources(){
    if(!this->gridTexture.loadFromFile("sources/tile_background.bmp")){
        std::cin.get();
        exit(0);
    }
    this->gridTexture.setSmooth(false);
    this->gridTexture.setRepeated(false);


    if(!this->highGradeTexture.loadFromFile("sources/grades.bmp")){
        std::cin.get();
        exit(0);
    }
    this->highGradeTexture.setSmooth(false);
    this->highGradeTexture.setRepeated(false);

    // if(!this->edditTexture.loadFromFile("sources/eddit.bmp")){
    //     std::cin.get();
    //     exit(0);
    // }
    // this->edditTexture.setSmooth(false);
    // this->edditTexture.setRepeated(false);

    if(!this->font.loadFromFile("sources/OpenSans-Light.ttf")){
        std::cin.get();
        exit(0);
    }
    this->gradeAvarageName.setFont(this->font);
    this->gradeAvarageName.setString("Text 1");
    this->gradeAvarageName.setCharacterSize(20);
    this->gradeAvarageName.setPosition(sf::Vector2f(100.f,20.f));
    this->gradeAvarageName.setFillColor(sf::Color(255,255,255));

    this->gradeAvarageRange.setFont(this->font);
    this->gradeAvarageRange.setString("Text 2");
    this->gradeAvarageRange.setCharacterSize(20);
    this->gradeAvarageRange.setPosition(sf::Vector2f(400.f,20.f));
    this->gradeAvarageRange.setFillColor(sf::Color(255,255,255));

}

void Program::initData(){
    std::vector<std::vector<std::string>> vdata;
    std::fstream file;
    file.open(DATA_FILE, std::ios::in);
    if(!file.good()){
        printf("can't read file %s!\n",DATA_FILE);
        std::cin.get();
        exit(0);
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
            std::cin.get();
            exit(0);
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

void Program::initShapes(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){

            if(this->data[i][j][0] == '-')
                this->tiles[i][j] = new EmptyTile(
                    TILE_SIZE,
                    TILE_POSITION
                    );
            else if(this->data[i][j][0] == '0' || this->data[i][j][0] == '1')
                this->tiles[i][j] = new GradeTile(
                    TILE_SIZE,
                    TILE_POSITION, 
                    this->data[i][j], 
                    this->gridTexture, 
                    this->highGradeTexture
                    );
            else
                this->tiles[i][j] = new TextTile(
                    TILE_SIZE,
                    TILE_POSITION,
                    this->data[i][j], 
                    this->font
                    );
        }
    }

    this->gradeAvarageName.setFont(this->font);
    this->gradeAvarageRange.setFont(this->font);
}

void Program::initWindow(){
    //                left margin +   sum of tiles width     + sum of separators between tiles   + right margin
    unsigned int windowWidth = 
        WINDOW_LEFT_MARGIN + 
        this->rows * TILE_HEIGHT + 
        (this->rows-1) * TILE_SEPARATOR + 
        WINDOW_RIGHT_MARGIN;
    //                   top margin +   sum of tiles heights    + sum of separators between tiles + bottom margin
    unsigned int windowHeight = 
        WINDOW_TOP_MARGIN + 
        this->lines * TILE_HEIGHT + 
        (this->lines-1) * TILE_SEPARATOR + 
        WINDOW_BOTTOM_MARGIN;
    
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::None);
    this->window->setPosition(sf::Vector2i((MAIN_WINDOW_WIDTH - windowWidth)/2,(MAIN_WINDOW_HEIGHT - windowHeight)/2));
    this->window->setFramerateLimit(FPS);
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
    this->loadSources();
    this->initData();
    this->initShapes();
    this->initWindow();
}

Program::~Program(){
    this->delShapes();
    // this->saveData();
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
            // else 
            //     for(int i=0; i<this->rows; i++){
            //         for(int j=0; j<this->lines; j++){
            //             this->tiles[i][j]->keyboardKeys(this->currentEvent.key.code);
            //         }
            //     }
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
    // "000000r0"
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
void Program::computeGradeAvarage(){
    float sumMin = 0.f, sumMax = 0.f;
    int gradesCount = 0;
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            if(this->data[i][j][0] == '+'){
                float min,max;
                if(this->getGradeFromSingleData(data[i][j],min,max)){
                    sumMin += min;
                    sumMax += max;
                    gradesCount++;
                }
                
            }
        }
    }
    this->gradeAvarageValueMin = sumMin / gradesCount;
    this->gradeAvarageValueMax = sumMax / gradesCount;
    // printf("%.2f - %.2f\n", this->gradeAvarageValueMin, this->gradeAvarageValueMax);
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
    this->computeGradeAvarage();
}

void Program::render(){
    this->window->clear(sf::Color(30,30,30));

    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->tiles[i][j]->render(this->window);
        }
    }

    this->window->draw(this->gradeAvarageName);
    this->window->draw(this->gradeAvarageRange);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
