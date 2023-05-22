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
    std::lock_guard<std::mutex> lock(mutex);
    if(!available){
        available = true;
        ship->setDock(nullptr);
        ship = nullptr;
        return true;
    }
    return false;
}


int Dock::getId(){
    std::lock_guard<std::mutex> lock(mutex);
    return id;
}

bool Dock::isAvailable(){
    std::lock_guard<std::mutex> lock(mutex);
    return available;
}

Ship *Dock::getShip(){
    std::lock_guard<std::mutex> lock(mutex);
    return ship;
}


