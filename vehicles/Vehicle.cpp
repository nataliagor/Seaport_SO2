//
// Created by natalia on 18.05.23.
//

#include "Vehicle.h"

Vehicle::Vehicle(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : id(id), capacityInLitres(capacityInLitres),
                                                                                      loadInLiters(loadInLiters), timeInPort(0), maxTimeInPort(maxTimeInPort){
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    loadStatus = loadInLiters == 0 ? LoadStatus::EMPTY : LoadStatus::LOADED;
}

Vehicle::~Vehicle() {}

bool Vehicle::isEmpty(){
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    return (loadStatus == LoadStatus::EMPTY);
}

bool Vehicle::isLoaded(){
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    return (loadStatus == LoadStatus::LOADED);
}

bool Vehicle::isBeingLoaded(){
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    return (loadStatus == LoadStatus::LOADING);
}

bool Vehicle::isBeingUnloaded(){
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    return (loadStatus == LoadStatus::UNLOADING);
}

bool Vehicle::isFull(){
    return (getLoadInLiters() == getCapacityInLitres());
}

int Vehicle::unload(int amount){
    if(getLoadInLiters() < amount) return -1;
    setLoadInLiters(getLoadInLiters() - amount);

    std::lock_guard<std::mutex> lock(loadStatusMutex);
    loadStatus = getLoadInLiters() > 0 ? LoadStatus::UNLOADING : LoadStatus::EMPTY;
    return getLoadInLiters();
}

int Vehicle::load(int amount){
    if(getLoadInLiters() + amount > getCapacityInLitres()) return -1;
    setLoadInLiters(getLoadInLiters() + amount);

    std::lock_guard<std::mutex> lock(loadStatusMutex);
    loadStatus = getLoadInLiters() < getCapacityInLitres() ? LoadStatus::LOADING : LoadStatus::LOADED;
    return getCapacityInLitres() - getLoadInLiters();
}

int Vehicle::getTimeInPort(){
    std::lock_guard<std::mutex> lock(timeInPortMutex);
    return timeInPort;
}

int Vehicle::getMaxTimeInPort(){
    std::lock_guard<std::mutex> lock(maxTimeInPortMutex);
    return maxTimeInPort;
}

int Vehicle::getId() const {
    return id;
}

int Vehicle::getCapacityInLitres() const{
    return capacityInLitres;
}

int Vehicle::getLoadInLiters(){
    std::lock_guard<std::mutex> lock(loadInLitersMutex);
    return loadInLiters;
}

void Vehicle::setLoadInLiters(int loadInLiters) {
    std::lock_guard<std::mutex> lock(loadInLitersMutex);
    Vehicle::loadInLiters = loadInLiters;
}
