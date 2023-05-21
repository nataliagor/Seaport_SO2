//
// Created by dell on 19.05.2023.
//

#include "Dock.h"
#include "../vehicles/Ship.h"

Dock::Dock(int id) : id(id), available(true), ship(nullptr) {}

Dock::~Dock() {}

bool Dock::occupyDock(Ship *newShip){
    std::lock_guard<std::mutex> lock(mutex);
    if(available){
        available = false;
        ship = newShip;
        newShip->setDock(this);
        return true;
    }
    return false;
}

bool Dock::freeDock(){
    if(!available){
        available = true;
        ship = nullptr;
        return true;
    }
    return false;
}
