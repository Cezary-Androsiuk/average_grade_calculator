#include "Program.hpp"

void Program::loadSources(){
    if(!this->tileTemplateTexture.loadFromFile("sources/GradeTile_template.bmp")){
        std::cin.get();
        exit(0);
    }
    this->tileTemplateTexture.setSmooth(false);
    this->tileTemplateTexture.setRepeated(false);

    
    if(!this->expectedGradeTexture.loadFromFile("sources/expected_grade.bmp")){
        std::cin.get();
        exit(0);
    }
    this->expectedGradeTexture.setSmooth(false);
    this->expectedGradeTexture.setRepeated(false);

    if(!this->currentGradeTexture.loadFromFile("sources/current_grade.bmp")){
        std::cin.get();
        exit(0);
    }
    this->currentGradeTexture.setSmooth(false);
    this->currentGradeTexture.setRepeated(false);

    if(!this->font.loadFromFile("sources/OpenSans-Light.ttf")){
        std::cin.get();
        exit(0);
    }
}

void Program::initData(){
    this->resetButtonCounter = RESET_BUTTON_NEEDED_ACTIONS_COUNT;
    this->resetButtonTimer = 0;
    this->resetButtonCounterTextVisible = false;
    this->dataShouldBeCleared = false;

    this->gradeAvarageValueMin = 0.f;
    this->gradeAvarageValueMax = 0.f;

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


    
    //                left margin + sum of tiles width + sum of separators between tiles + right margin
    this->windowWidth = 
        WINDOW_LEFT_MARGIN + 
        this->rows * TILE_HEIGHT + 
        (this->rows-1) * TILE_SEPARATOR + 
        WINDOW_RIGHT_MARGIN;
    //                   top margin + sum of tiles heights + sum of separators between tiles + bottom margin
    this->windowHeight = 
        WINDOW_TOP_MARGIN + 
        this->lines * TILE_HEIGHT + 
        (this->lines-1) * TILE_SEPARATOR + 
        WINDOW_BOTTOM_MARGIN;
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
                    this->tileTemplateTexture,
                    this->expectedGradeTexture,
                    this->currentGradeTexture
                    );
            else
                this->tiles[i][j] = new TextTile(
                    TILE_SIZE,
                    TILE_POSITION,
                    this->data[i][j], 
                    this->font,
                    10
                    );
        }
    }

    this->gradeAvarageName.setFont(this->font);
    this->gradeAvarageName.setString(L"Możliwa Średnia Ocen");
    this->gradeAvarageName.setCharacterSize(20);
    this->gradeAvarageName.setFillColor(sf::Color(200,200,200));
    this->gradeAvarageName.setPosition(sf::Vector2f(0.f,20.f));
    this->gradeAvarageName.setPosition(sf::Vector2f(
        ( (float)this->windowWidth - this->gradeAvarageName.getGlobalBounds().width)/2,
        this->gradeAvarageName.getPosition().y));
    
    this->gradeAvarageRange.setFont(this->font);
    this->gradeAvarageRange.setString("0.00");
    this->gradeAvarageRange.setCharacterSize(28);
    this->gradeAvarageRange.setStyle(sf::Text::Bold);
    this->gradeAvarageRange.setFillColor(sf::Color(255,255,255));
    this->gradeAvarageRange.setPosition(sf::Vector2f(0.f,50.f));

    this->resetButton.setSize(sf::Vector2f(80.f,50.f));
    this->resetButton.setPosition(sf::Vector2f(
        this->windowWidth - 10.f - this->resetButton.getSize().x,
        this->windowHeight - 10.f - this->resetButton.getSize().y
        ));
    this->resetButton.setFillColor(sf::Color(40,40,40));

    this->resetButtonText.setFont(this->font);
    this->resetButtonText.setString("RESET");
    this->resetButtonText.setCharacterSize(16);
    this->resetButtonText.setFillColor(sf::Color(160,160,160));
    this->resetButtonText.setPosition(sf::Vector2f(
        this->resetButton.getGlobalBounds().left + 18.f,
        this->resetButton.getGlobalBounds().top + 16.f
    ));

    this->resetButtonCounterText.setFont(this->font);
    this->resetButtonCounterText.setString("5");
    this->resetButtonCounterText.setCharacterSize(16);
    this->resetButtonCounterText.setFillColor(sf::Color(160,160,160));
    this->resetButtonCounterText.setPosition(sf::Vector2f(
        this->resetButton.getGlobalBounds().left + 36.f,
        this->resetButton.getGlobalBounds().top + 25.f
    ));
}

void Program::initWindow(){
    this->videoMode = sf::VideoMode(windowWidth, windowHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Average Grade Calculator", sf::Style::None);
    this->window->setPosition(sf::Vector2i((MAIN_WINDOW_WIDTH - this->windowWidth)/2,(MAIN_WINDOW_HEIGHT - this->windowHeight)/2));
    this->window->setFramerateLimit(FPS);
    printf("window: %ux%u\n",this->window->getSize().x, this->window->getSize().y);
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

void Program::clearData(){
    std::fstream file;
    file.open(DATA_FILE, std::ios::out);
    if(!file.good()){
        printf("can't open data file in path %s!\n",DATA_FILE);
        this->deleteData();
        return;
    }

    file << "-;?(16);?(16);?(16);?(16);\n";
    file << "?(16);10[00000]g0;10[00000]g0;10[00000]g0;10[00000]g0;\n";
    file << "?(16);10[00000]g0;10[00000]g0;10[00000]g0;10[00000]g0;\n";
    file << "?(16);10[00000]g0;10[00000]g0;10[00000]g0;10[00000]g0;\n";

    file.close();

    this->deleteData();
}

void Program::saveData(){
    // save to file
    std::fstream file;
    file.open(DATA_FILE, std::ios::out);
    if(!file.good()){
        printf("can't open data file in path %s!\n",DATA_FILE);
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
    if(this->dataShouldBeCleared){
        this->clearData();
        printf("Data was cleared correctly! Now you can adjust text in file.\n");
    }
    else{
        this->saveData();
    }
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
            if(this->currentEvent.mouseButton.button == sf::Mouse::Left){
                for(int i=0; i<this->rows; i++)
                    for(int j=0; j<this->lines; j++)
                        this->tiles[i][j]->mouseLeftPressed();
                
                // reset button
                if(this->resetButton.getGlobalBounds().contains(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)))){
                    this->resetButtonCounter--;
                    this->resetButtonTimer = 0;
                    if(this->resetButtonCounter == 0){
                        this->resetButtonCounter = RESET_BUTTON_NEEDED_ACTIONS_COUNT;
                        // reset ALL function
                        printf("RESET!\n");
                        this->dataShouldBeCleared = true;
                        this->window->close();
                    }
                }
            }
            else if(this->currentEvent.mouseButton.button == sf::Mouse::Right){
                for(int i=0; i<this->rows; i++)
                    for(int j=0; j<this->lines; j++)
                        this->tiles[i][j]->mouseRightPressed();
            }
            else if(this->currentEvent.mouseButton.button == sf::Mouse::Middle){
                for(int i=0; i<this->rows; i++)
                    for(int j=0; j<this->lines; j++)
                        this->tiles[i][j]->mouseMiddlePressed();    
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

void Program::updateData(){
    // update this->data depends on tiles data
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->data[i][j] = this->tiles[i][j]->getData();
        }
    }
}

void Program::updateText(){
    if(this->gradeAvarageValueMin != this->gradeAvarageValueMax)
        this->gradeAvarageRange.setString(
            std::to_string(
                this->gradeAvarageValueMin).substr(0,4) + 
                " - " + 
                std::to_string(this->gradeAvarageValueMax).substr(0,4));
    else
        this->gradeAvarageRange.setString(std::to_string(this->gradeAvarageValueMin).substr(0,4));

    this->gradeAvarageRange.setPosition(sf::Vector2f(
        ( (float)this->windowWidth - this->gradeAvarageRange.getGlobalBounds().width)/2,
        this->gradeAvarageRange.getPosition().y));
    

}

void Program::updateResetButton(){
    if(this->resetButtonCounter < RESET_BUTTON_NEEDED_ACTIONS_COUNT){
        this->resetButtonTimer++;
        if(this->resetButtonTimer >= RESET_BUTTON_TIME){
            this->resetButtonTimer = 0;
            this->resetButtonCounter++;
        }
        this->resetButtonText.setPosition(sf::Vector2f(
            this->resetButton.getGlobalBounds().left + 18.f,
            this->resetButton.getGlobalBounds().top + 7.f
        ));
        this->resetButtonCounterTextVisible = true;
        if(this->resetButtonCounter < RESET_BUTTON_NEEDED_ACTIONS_COUNT)
            this->resetButtonCounterText.setString(std::to_string(this->resetButtonCounter));
    }
    else{
        this->resetButtonText.setPosition(sf::Vector2f(
            this->resetButton.getGlobalBounds().left + 18.f,
            this->resetButton.getGlobalBounds().top + 16.f
        ));
        this->resetButtonCounterTextVisible = false;
    }
    
}

void Program::mouseHoverDetection(){
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            this->tiles[i][j]->mouseHoverUpdate(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
        }
    }
}

bool Program::getGradeFromSingleData(const std::string& singleData, float& min, float& max) const{
    // only enabled GradeTiles could went in
    // "10[00000]000"
    //  0123456789AB
    // enabled locked [expected grade] grade_type grade2 grade

    // this methond is true nightmare
    
    if(singleData[10] == '1'){
        // "1_[_____]_1_"
        switch (singleData[11]){
        case '0':
            // "1_[_____]_10"
            if(singleData.find("[00000]",2) != std::string::npos){
                // "1_[00000]_10"
                min = 2.f;
                max = 2.f;
            }
            else{
                float tmp_min = 0.f;
                float tmp_max = 0.f;
                // "1_[1____]_10"
                tmp_min = 3.f;
                if(singleData[3] == '0'){
                    // "1_[01___]_10"
                    tmp_min = 3.5f;
                    if(singleData[4] == '0'){
                        // "1_[001__]_10"
                        tmp_min = 4.f;
                        if(singleData[5] == '0'){
                            // "1_[0001_]_10"
                            tmp_min = 4.5f;
                            if(singleData[6] == '0'){
                                // "1_[00001]_10"
                                tmp_min = 5.f;
                            }
                        }
                    }
                }
                // "1_[____1]_10"
                tmp_max = 5.f;
                if(singleData[7] == '0'){
                    // "1_[___10]_10"
                    tmp_max = 4.5f;
                    if(singleData[6] == '0'){
                        // "1_[__100]_10"
                        tmp_max = 4.f;
                        if(singleData[5] == '0'){
                            // "1_[_1000]_10"
                            tmp_max = 3.5f;
                            if(singleData[4] == '0'){
                                // "1_[10000]_10"
                                tmp_max = 3.f;
                            }
                        }
                    }
                }
                min = (2.f + tmp_min) / 2;
                max = (2.f + tmp_max) / 2;
            }
            break;
        case '1':
            // "1_[_____]_11"
            // 2 & 2
            min = 2.f;
            max = 2.f;
            break;
        case '2':
            // "1_[_____]_12"
            // 2 & 3
            min = 2.5f;
            max = 2.5f;
            break;
        case '3':
            // "1_[_____]_13"
            // 2 & 3.5
            min = 2.75f;
            max = 2.75f;
            break;
        case '4':
            // "1_[_____]_14"
            // 2 & 4
            min = 3.f;
            max = 3.f;
            break;
        case '5':
            // "1_[_____]_15"
            // 2 & 4.5
            min = 3.25f;
            max = 3.25f;
            break;
        case '6':
            // "1_[_____]_16"
            // 2 & 5
            min = 3.5f;
            max = 3.5f;
            break;
        default: printf("getGradeFromSingleData() ?\n");
            break;
        }
    }
    else{
        // "1_[_____]_0_"
        switch (singleData[11]){
        case '0':
            // "1_[_____]_00"
            if(singleData.find("[00000]",2) != std::string::npos){
                // "1_[00000]_00"
                // unknown grade and unknown range
                // those tiles are not used in computing avarage grade
                return false;    
            }
            else{
                float tmp_min = 0.f;
                float tmp_max = 0.f;
                // "1_[1____]_00"
                tmp_min = 3.f;
                if(singleData[3] == '0'){
                    // "1_[01___]_00"
                    tmp_min = 3.5f;
                    if(singleData[4] == '0'){
                        // "1_[001__]_00"
                        tmp_min = 4.f;
                        if(singleData[5] == '0'){
                            // "1_[0001_]_00"
                            tmp_min = 4.5f;
                            if(singleData[6] == '0'){
                                // "1_[00001]_00"
                                tmp_min = 5.f;
                            }
                        }
                    }
                }
                // "1_[____1]_00"
                tmp_max = 5.f;
                if(singleData[7] == '0'){
                    // "1_[___10]_00"
                    tmp_max = 4.5f;
                    if(singleData[6] == '0'){
                        // "1_[__100]_00"
                        tmp_max = 4.f;
                        if(singleData[5] == '0'){
                            // "1_[_1000]_00"
                            tmp_max = 3.5f;
                            if(singleData[4] == '0'){
                                // "1_[10000]_00"
                                tmp_max = 3.f;
                            }
                        }
                    }
                }
                min = tmp_min;
                max = tmp_max;
            }
            break;
        case '1':
            // "1_[_____]_01"
            // 2
            min = 2.f;
            max = 2.f;
            break;
        case '2':
            // "1_[_____]_02"
            // 3
            min = 3.f;
            max = 3.f;
            break;
        case '3':
            // "1_[_____]_03"
            // 3.5
            min = 3.5f;
            max = 3.5f;
            break;
        case '4':
            // "1_[_____]_04"
            // 4
            min = 4.f;
            max = 4.f;
            break;
        case '5':
            // "1_[_____]_05"
            // 4.5
            min = 4.5f;
            max = 4.5f;
            break;
        case '6':
            // "1_[_____]_06"
            // 5
            min = 5.f;
            max = 5.f;
            break;
        default: printf("getGradeFromSingleData() ?\n");
            break;
        }
    }
    return true;
}
void Program::computeGradeAvarage(){
    float sumMin = 0.f, sumMax = 0.f;
    int gradesCount = 0;
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->lines; j++){
            if(this->data[i][j][0] == '1'){
                // only enabled
                float min,max;
                if(this->getGradeFromSingleData(data[i][j],min,max)){
                    sumMin += min;
                    sumMax += max;
                    gradesCount++;
                }
                
            }
        }
    }
    if(gradesCount != 0){
        this->gradeAvarageValueMin = sumMin / gradesCount;
        this->gradeAvarageValueMax = sumMax / gradesCount;
    }
    else{
        this->gradeAvarageValueMin = 0.f;
        this->gradeAvarageValueMax = 0.f;

    }
}

void Program::update(){
    this->pollEvent();

    this->mouseHoverDetection();
    this->updateData();
    this->computeGradeAvarage();
    this->updateText();
    this->updateResetButton();
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

    this->window->draw(this->resetButton);
    this->window->draw(this->resetButtonText);
    if(this->resetButtonCounterTextVisible)
        this->window->draw(this->resetButtonCounterText);

    this->window->display();
}

const bool Program::running() const{
    return this->window->isOpen();
}
