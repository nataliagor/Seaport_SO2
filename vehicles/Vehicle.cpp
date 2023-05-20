//
// Created by natalia on 18.05.23.
//

#include "Vehicle.h"

Vehicle::Vehicle() {}

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
