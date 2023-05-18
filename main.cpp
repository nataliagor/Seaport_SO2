#include <iostream>
#include "Seaport.h"
#include "Seaport.cpp"
#include "PortAdministrator.h"
#include "PortAdministrator.cpp"
#include "view/IView.h"
#include "view/ConsoleView.h"
#include "view/ConsoleView.cpp"
#include "view/NcursesView.h"
#include "view/NcursesView.cpp"
#include "vehicles/Vehicle.h"
#include "vehicles/Ship.h"
#include "vehicles/Ship.cpp"
#include "vehicles/Truck.h"
#include "vehicles/Truck.cpp"



int main() {
    Seaport* seaPost = new Seaport();
    seaPost->startWorking();
    return 0;
}
