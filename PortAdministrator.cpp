//
// Created by natalia on 18.05.23.
//

#include "PortAdministrator.h"

PortAdministrator::PortAdministrator(IView &view) : view(view) {}

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

bool PortAdministrator::givePermissionToLoadedToDock(Dock* dock){
    std::lock_guard<std::mutex> lock(loadedShipsQueueMutex);
    if(!loadedShipsToDockPriorityQueue.empty()){
        Ship* ship = loadedShipsToDockPriorityQueue.top();
        dock->occupyDock(ship);
        loadedShipsToDockPriorityQueue.pop();
        view.occupyDock(dock->getId(), ship->getId());
    }else return false;
    return true;
}

bool PortAdministrator::givePermissionToEmptyToDock(Dock* dock){
    std::lock_guard<std::mutex> lock(emptyShipsQueueMutex);
    if(!emptyShipsToDockPriorityQueue.empty()){
        Ship* ship = emptyShipsToDockPriorityQueue.top();
        dock->occupyDock(ship);
        emptyShipsToDockPriorityQueue.pop();
        view.occupyDock(dock->getId(), ship->getId());
    }else return false;
    return true;
}

int PortAdministrator::givePermissionsToLeaveDock(int numberOfLoadedShips){
    std::lock_guard<std::mutex> lock(leavingShipsQueueMutex);
    while(!shipsToLeavePriorityQueue.empty()){
        if(shipsToLeavePriorityQueue.top()->isLoaded()){
            Dock* dock = shipsToLeavePriorityQueue.top()->getDock();
            dock->freeDock();
            numberOfLoadedShips--;
            view.freeDock(dock->getId());
        }
        shipsToLeavePriorityQueue.pop();
    }
    return numberOfLoadedShips;
}

void PortAdministrator::addToEmptyTrucksToParkQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(emptyTrucksQueueMutex);
    emptyTrucksToParkPriorityQueue.push(truck);
}

void PortAdministrator::addToLoadedTrucksToParkQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(loadedTrucksQueueMutex);
    loadedTrucksToParkPriorityQueue.push(truck);
}

void PortAdministrator::addToTrucksToLeaveQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(leavingTrucksQueueMutex);
    trucksToLeavePriorityQueue.push(truck);
}

bool PortAdministrator::givePermissionToLoadedToPark(TruckParkingArea* truckParkingArea){
    std::lock_guard<std::mutex> lock(emptyTrucksQueueMutex);
    if(!loadedTrucksToParkPriorityQueue.empty()){
        Truck* truck = loadedTrucksToParkPriorityQueue.top();
                truckParkingArea->occupyParkingArea(truck);
        loadedTrucksToParkPriorityQueue.pop();
        view.occupyTruckParkingArea(truckParkingArea->getId(), truck->getId());
    }else return false;
    return true;
}

bool PortAdministrator::givePermissionToEmptyToPark(TruckParkingArea* truckParkingArea){
    std::lock_guard<std::mutex> lock(loadedTrucksQueueMutex);
    if(!emptyTrucksToParkPriorityQueue.empty()){
        Truck* truck = emptyTrucksToParkPriorityQueue.top();
        truckParkingArea->occupyParkingArea(truck);
        emptyTrucksToParkPriorityQueue.pop();
        view.occupyTruckParkingArea(truckParkingArea->getId(), truck->getId());
    }else return false;
    return true;
}

int PortAdministrator::givePermissionsToLeaveParking(int numberOfLoadedTrucks){
    std::lock_guard<std::mutex> lock(leavingTrucksQueueMutex);
    while(!trucksToLeavePriorityQueue.empty()){
        if(trucksToLeavePriorityQueue.top()->isLoaded()){
            TruckParkingArea* truckParkingArea = trucksToLeavePriorityQueue.top()->getTruckParkingArea();
            truckParkingArea->freeParkingArea();
            numberOfLoadedTrucks--;
            view.freeTruckParkingArea(truckParkingArea->getId());
        }
        trucksToLeavePriorityQueue.pop();
    }
    return numberOfLoadedTrucks;
}



