#include "include/include.hpp"
#include "include/Program/Program.hpp"

int main(){
    Program app;
    while(app.running()){
        app.update();
        app.render();
    }
}