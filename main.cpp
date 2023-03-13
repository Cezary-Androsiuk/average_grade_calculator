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

TODO grade value 1/4  &  3/4 change to grade 2 in first term
TODO text height center
TODO DescriptionNotification with full name of object

*/

