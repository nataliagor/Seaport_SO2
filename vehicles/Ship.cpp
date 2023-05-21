//
// Created by natalia on 18.05.23.
//

#include "Ship.h"
#include "../stoppingPlaces/Dock.h"

Ship::Ship(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : Vehicle(id, capacityInLitres, loadInLiters, maxTimeInPort) {
    dock = nullptr;
    timeInPort = 0;     //tutaj zaczac odliczanie
}

Ship::~Ship() {}

bool Ship::leaveSeaport(){
    if(dock != nullptr){
        dock->freeDock();           //? czy tutaj dodac pytanie do aministrator i on zwalnia dock
        dock = nullptr;
        return true;
    }
    return false;
}

void Ship::setDock(Dock *dock) {
    Ship::dock = dock;
}

Dock* Ship::getDock() const {
    return dock;
}




