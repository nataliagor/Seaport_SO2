//
// Created by natalia on 18.05.23.
//

#include "Vehicle.h"

Vehicle::Vehicle(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : id(id), capacityInLitres(capacityInLitres),
                                                                                      loadInLiters(loadInLiters), timeInPort(0), maxTimeInPort(maxTimeInPort){
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
    return (loadInLiters == capacityInLitres);
}

int Vehicle::unload(int amount){
    if(loadInLiters < amount) return -1;

    loadInLiters -= amount;
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    loadStatus = loadInLiters > 0 ? LoadStatus::UNLOADING : LoadStatus::EMPTY;
    return loadInLiters;
}

int Vehicle::load(int amount){
    if(loadInLiters > capacityInLitres) return -1;

    loadInLiters += amount;
    std::lock_guard<std::mutex> lock(loadStatusMutex);
    loadStatus = loadInLiters < capacityInLitres ? LoadStatus::LOADING : LoadStatus::LOADED;
    return capacityInLitres - loadInLiters;
}

int Vehicle::getTimeInPort(){
    return timeInPort;
}

int Vehicle::getMaxTimeInPort(){
    return maxTimeInPort;
}

int Vehicle::getId(){
    return id;
}
