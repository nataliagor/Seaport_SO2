#include <iostream>
#include "Seaport.h"
//#include "Seaport.cpp"
//#include "PortAdministrator.h"
//#include "PortAdministrator.cpp"
//#include "view/IView.h"
//#include "view/ConsoleView.h"
//#include "view/ConsoleView.cpp"
//#include "view/NcursesView.h"
//#include "view/NcursesView.cpp"



int main() {
    Seaport* seaPost = new Seaport(5);
    seaPost->startWorking();
    return 0;
}
