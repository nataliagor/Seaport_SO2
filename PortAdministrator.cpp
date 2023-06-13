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

void PortAdministrator::addToLoadedShipsToLeaveQueue(Ship* ship){
    std::lock_guard<std::mutex> lock(loadedLeavingShipsQueueMutex);
    loadedShipsToLeavePriorityQueue.push(ship);
}

void PortAdministrator::addToEmptyShipsToLeaveQueue(Ship* ship){
    std::lock_guard<std::mutex> lock(emptyLeavingShipsQueueMutex);
    emptyShipsToLeavePriorityQueue.push(ship);
}

bool PortAdministrator::givePermissionToLoadedToDock(Dock* dock){
    std::lock_guard<std::mutex> lock(loadedShipsQueueMutex);
    if(!loadedShipsToDockPriorityQueue.empty()){
        Ship* ship = loadedShipsToDockPriorityQueue.top();
        dock->occupyDock(ship);
        loadedShipsToDockPriorityQueue.pop();
        view.occupyDock(dock->getId(), ship->getId(), ship->getCapacityInLitres(), ship->getLoadInLiters());
    }else return false;
    return true;
}

bool PortAdministrator::givePermissionToEmptyToDock(Dock* dock){
    std::lock_guard<std::mutex> lock(emptyShipsQueueMutex);
    if(!emptyShipsToDockPriorityQueue.empty()){
        Ship* ship = emptyShipsToDockPriorityQueue.top();
        dock->occupyDock(ship);
        emptyShipsToDockPriorityQueue.pop();
        view.occupyDock(dock->getId(), ship->getId(), ship->getCapacityInLitres(), ship->getLoadInLiters());
    }else return false;
    return true;
}

int PortAdministrator::giveLoadedPermissionsToLeaveDock(int numberOfLoadedShips){
    std::lock_guard<std::mutex> lock(loadedLeavingShipsQueueMutex);
    while(!loadedShipsToLeavePriorityQueue.empty()){
        if(loadedShipsToLeavePriorityQueue.top()->isLoaded()){
            Dock* dock = loadedShipsToLeavePriorityQueue.top()->getDock();
            dock->freeDock();
            numberOfLoadedShips--;
            view.freeDock(dock->getId());
        }
        loadedShipsToLeavePriorityQueue.pop();
    }
    return numberOfLoadedShips;
}

int PortAdministrator::giveEmptyPermissionsToLeaveDock(int numberOfEmptyShips){
    std::lock_guard<std::mutex> lock(emptyLeavingShipsQueueMutex);
    while(!emptyShipsToLeavePriorityQueue.empty()){
        if(emptyShipsToLeavePriorityQueue.top()->isEmpty()){
            Dock* dock = emptyShipsToLeavePriorityQueue.top()->getDock();
            dock->freeDock();
            numberOfEmptyShips--;
            view.freeDock(dock->getId());
        }
        emptyShipsToLeavePriorityQueue.pop();
    }
    return numberOfEmptyShips;
}

void PortAdministrator::addToEmptyTrucksToParkQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(emptyTrucksQueueMutex);
    emptyTrucksToParkPriorityQueue.push(truck);
}

void PortAdministrator::addToLoadedTrucksToParkQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(loadedTrucksQueueMutex);
    loadedTrucksToParkPriorityQueue.push(truck);
}

void PortAdministrator::addToLoadedTrucksToLeaveQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(loadedLeavingTrucksQueueMutex);
    loadedTrucksToLeavePriorityQueue.push(truck);
}

void PortAdministrator::addToEmptyTrucksToLeaveQueue(Truck* truck){
    std::lock_guard<std::mutex> lock(emptyLeavingTrucksQueueMutex);
    emptyTrucksToLeavePriorityQueue.push(truck);
}

bool PortAdministrator::givePermissionToLoadedToPark(TruckParkingArea* truckParkingArea){
    std::lock_guard<std::mutex> lock(emptyTrucksQueueMutex);
    if(!loadedTrucksToParkPriorityQueue.empty()){
        Truck* truck = loadedTrucksToParkPriorityQueue.top();
                truckParkingArea->occupyParkingArea(truck);
        loadedTrucksToParkPriorityQueue.pop();
        view.occupyTruckParkingArea(truckParkingArea->getId(), truck->getId(), truck->getCapacityInLitres(), truck->getLoadInLiters());
    }else return false;
    return true;
}

bool PortAdministrator::givePermissionToEmptyToPark(TruckParkingArea* truckParkingArea){
    std::lock_guard<std::mutex> lock(loadedTrucksQueueMutex);
    if(!emptyTrucksToParkPriorityQueue.empty()){
        Truck* truck = emptyTrucksToParkPriorityQueue.top();
        truckParkingArea->occupyParkingArea(truck);
        emptyTrucksToParkPriorityQueue.pop();
        view.occupyTruckParkingArea(truckParkingArea->getId(), truck->getId(), truck->getCapacityInLitres(), truck->getLoadInLiters());
    }else return false;
    return true;
}

int PortAdministrator::giveLoadedPermissionsToLeaveParking(int numberOfLoadedTrucks){
    std::lock_guard<std::mutex> lock(loadedLeavingTrucksQueueMutex);
    while(!loadedTrucksToLeavePriorityQueue.empty()){
        if(loadedTrucksToLeavePriorityQueue.top()->isLoaded()){
            TruckParkingArea* truckParkingArea = loadedTrucksToLeavePriorityQueue.top()->getTruckParkingArea();
            truckParkingArea->freeParkingArea();
            numberOfLoadedTrucks--;
            view.freeTruckParkingArea(truckParkingArea->getId());
        }
        loadedTrucksToLeavePriorityQueue.pop();
    }
    return numberOfLoadedTrucks;
}

int PortAdministrator::giveEmptyPermissionsToLeaveParking(int numberOfEmptyTrucks){
    std::lock_guard<std::mutex> lock(emptyLeavingTrucksQueueMutex);
    while(!emptyTrucksToLeavePriorityQueue.empty()){
        if(emptyTrucksToLeavePriorityQueue.top()->isEmpty()){
            TruckParkingArea* truckParkingArea = emptyTrucksToLeavePriorityQueue.top()->getTruckParkingArea();
            truckParkingArea->freeParkingArea();
            numberOfEmptyTrucks--;
            view.freeTruckParkingArea(truckParkingArea->getId());
        }
        emptyTrucksToLeavePriorityQueue.pop();
    }
    return numberOfEmptyTrucks;
}



