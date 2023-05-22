//
// Created by natalia on 18.05.23.
//

#include "Ship.h"
#include "../stoppingPlaces/Dock.h"

Ship::Ship(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : Vehicle(id, capacityInLitres, loadInLiters, maxTimeInPort) {
    dock = nullptr;
    timeInPort = 0;     //tutaj zaczac odliczanie czasu //TODO
}

Ship::~Ship() {}

bool Ship::leaveSeaport(){
    if(dock != nullptr){
        dock->freeDock();
        dock = nullptr;
        return true;
    }
    return false;
}

void Ship::setDock(Dock *dock) {
    std::lock_guard<std::mutex> lock(dockMutex);
    Ship::dock = dock;
}

Dock* Ship::getDock(){
    std::lock_guard<std::mutex> lock(dockMutex);
    return dock;
}




