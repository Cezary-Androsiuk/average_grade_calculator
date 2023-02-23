#include "include/include.hpp"
#include "include/Program/Program.hpp"
// g++ main.cpp -o bin/main include/Program/Program.cpp -lsfml-graphics -lsfml-window -lsfml-system; ./bin/main

int main(){
    Program app;
    while(app.running()){
        app.update();
        app.render();
    }
}