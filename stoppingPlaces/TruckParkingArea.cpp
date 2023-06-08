//
// Created by dell on 19.05.2023.
//

#include "TruckParkingArea.h"
#include "../vehicles/Truck.h"

TruckParkingArea::TruckParkingArea(int id) : id(id), available(true), truck(nullptr) {}

TruckParkingArea::~TruckParkingArea() {}

bool TruckParkingArea::occupyParkingArea(Truck *newTruck){
    if(isAvailable()){
        setAvailable(false);
        std::lock_guard<std::mutex> lock(truckMutex);
        truck = newTruck;
        newTruck->setTruckParkingArea(this);
        return true;
    }
    return false;
}

bool TruckParkingArea::freeParkingArea(){
    if(!isAvailable()){
        setAvailable(true);
        std::lock_guard<std::mutex> lock(truckMutex);
        truck->setTruckParkingArea(nullptr);
        truck = nullptr;
        return true;
    }
    return false;
}

int TruckParkingArea::getId(){
    std::lock_guard<std::mutex> lock(idMutex);
    return id;
}

bool TruckParkingArea::isAvailable(){
    std::lock_guard<std::mutex> lock(availableMutex);
    return available;
}

Truck *TruckParkingArea::getTruck(){
    std::lock_guard<std::mutex> lock(truckMutex);
    return truck;
}

void TruckParkingArea::setAvailable(bool available) {
    std::lock_guard<std::mutex> lock(availableMutex);
    TruckParkingArea::available = available;
}
