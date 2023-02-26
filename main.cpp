#include "include/include.hpp"
#include "include/Program/Program.hpp"
// g++ main.cpp -o main include/Program/Program.cpp include/Tile/Tile.cpp include/GradeTile/GradeTile.cpp include/TextTile/TextTile.cpp -lsfml-graphics -lsfml-window -lsfml-system; ./main

int main(){
    Program app;
    while(app.running()){
        app.update();
        app.render();
    }
}
