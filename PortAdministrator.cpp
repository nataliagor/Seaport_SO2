//
// Created by natalia on 18.05.23.
//

#include "PortAdministrator.h"

PortAdministrator::PortAdministrator() {}

PortAdministrator::~PortAdministrator() {}

void PortAdministrator::addToEmptyShipsToDockQueue(Ship* ship){
    std::lock_guard<std::mutex> lock(emptyShipsQueueMutex);
    emptyShipsToDockPriorityQueue.push(ship);
}

void PortAdministrator::addToLoadedShipsToDockQueue(Ship* ship) {
    std::lock_guard<std::mutex> lock(loadedShipsQueueMutex);
    loadedShipsToDockPriorityQueue.push(ship);
}

void PortAdministrator::addToShipsToLeaveQueue(Ship* ship){
    std::lock_guard<std::mutex> lock(leavingShipsQueueMutex);
    shipsToLeavePriorityQueue.push(ship);
}

void PortAdministrator::givePermissionToLoadedToDock(Dock* dock){
    std::lock_guard<std::mutex> lock(loadedShipsQueueMutex);
    if(!loadedShipsToDockPriorityQueue.empty()){
        dock->occupyDock(loadedShipsToDockPriorityQueue.top());
        loadedShipsToDockPriorityQueue.pop();
    }
}

void PortAdministrator::givePermissionToEmptyToDock(Dock* dock){
    std::lock_guard<std::mutex> lock(emptyShipsQueueMutex);
    if(!emptyShipsToDockPriorityQueue.empty()){
        dock->occupyDock(emptyShipsToDockPriorityQueue.top());
        emptyShipsToDockPriorityQueue.pop();
    }
}

int PortAdministrator::givePermissionsToLeaveDock(int numberOfLoadedShips){
    std::lock_guard<std::mutex> lock(leavingShipsQueueMutex);
    while(!shipsToLeavePriorityQueue.empty()){
        shipsToLeavePriorityQueue.top()->getDock()->freeDock();
        shipsToLeavePriorityQueue.pop();
        numberOfLoadedShips--;
    }
    return numberOfLoadedShips;
}

