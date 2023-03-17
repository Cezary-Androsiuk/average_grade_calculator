#include "include/include.hpp"
#include "include/Program/Program.hpp"
// g++ main.cpp -o main include/Program/Program.cpp include/Tile/Tile.cpp include/GradeTile/GradeTile.cpp include/TextTile/TextTile.cpp include/EmptyTile/EmptyTile.cpp -lsfml-graphics -lsfml-window -lsfml-system; ./main

int main(){
    Program app;
    while(app.running()){
        app.update();
        app.render();
    }
}

/*

// TODO text height center (skipped, cause exist problem with text position c: )
TODO DescriptionNotification with full name of object

*/

