//
// Created by dell on 19.05.2023.
//

#include "Dock.h"
#include "../vehicles/Ship.h"

Dock::Dock(int id) : id(id), available(true), ship(nullptr) {}

Dock::~Dock() {}

bool Dock::occupyDock(Ship *newShip){
    if(isAvailable()){
        setAvailable(false);
        std::lock_guard<std::mutex> lock(shipMutex);
        ship = newShip;
        newShip->setDock(this);
        return true;
    }
    return false;
}

bool Dock::freeDock(){;
    if(!isAvailable()){
        setAvailable(true);
        std::lock_guard<std::mutex> lock(shipMutex);
        ship->setDock(nullptr);
        ship = nullptr;
        return true;
    }
    return false;
}


int Dock::getId(){
    std::lock_guard<std::mutex> lock(idMutex);
    return id;
}

bool Dock::isAvailable(){
    std::lock_guard<std::mutex> lock(availableMutex);
    return available;
}

Ship *Dock::getShip(){
    std::lock_guard<std::mutex> lock(shipMutex);
    return ship;
}

void Dock::setAvailable(bool available) {
    std::lock_guard<std::mutex> lock(availableMutex);
    Dock::available = available;
}


