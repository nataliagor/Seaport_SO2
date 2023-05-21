//
// Created by natalia on 18.05.23.
//

#include "Vehicle.h"
int id;
int capacityInLitres;
int loadInLiters;
LoadStatus loadStatus;
int timeInPort;
int maxTimeInPort;

Vehicle::Vehicle(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : id(id), capacityInLitres(capacityInLitres),
                                                                                      loadInLiters(loadInLiters), timeInPort(0), maxTimeInPort(maxTimeInPort){
    loadStatus = loadInLiters == 0 ? LoadStatus::EMPTY : LoadStatus::LOADED;
}

Vehicle::~Vehicle() {}

bool Vehicle::isEmpty(){
    return (loadStatus == LoadStatus::EMPTY);
}

bool Vehicle::isLoaded(){
    return (loadStatus == LoadStatus::LOADED);
}

bool Vehicle::isFull() const{
    return (loadInLiters == capacityInLitres);
}

int Vehicle::unload(int amount){
    if(loadInLiters < amount) return -1;

    loadInLiters -= amount;
    loadStatus = loadInLiters > 0 ? LoadStatus::UNLOADING : LoadStatus::EMPTY;
    return loadInLiters;
}

int Vehicle::load(int amount){
    if(loadInLiters > capacityInLitres) return -1;

    loadInLiters += amount;
    loadStatus = loadInLiters < capacityInLitres ? LoadStatus::LOADING : LoadStatus::LOADED;
    return capacityInLitres - loadInLiters;
}

int Vehicle::getTimeInPort(){
    return timeInPort;
}

int Vehicle::getMaxTimeInPort(){
    return maxTimeInPort;
}
