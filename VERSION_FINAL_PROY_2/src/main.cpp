#include <conio.h>
#include "Menu/Menu.h"

int main(){
    srand(time(nullptr));
    Menu menu;
    menu.jugar();
    cout<<"\nPresione una tecla para finalizar el programa...";
    getch();
    return 0;
}