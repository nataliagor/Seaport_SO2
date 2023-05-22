//
// Created by dell on 19.05.2023.
//

#include "TruckParkingArea.h"
#include "../vehicles/Truck.h"

TruckParkingArea::TruckParkingArea(int id) : id(id), available(true), truck(nullptr) {}

TruckParkingArea::~TruckParkingArea() {}

bool TruckParkingArea::occupyParkingArea(Truck *newTruck){
    std::lock_guard<std::mutex> lock(mutex);
    if(available){
        available = false;
        truck = newTruck;
        newTruck->setTruckParkingArea(this);
        return true;
    }
    return false;
}

bool TruckParkingArea::freeParkingArea(){
    std::lock_guard<std::mutex> lock(mutex);
    if(!available){
        available = true;
        truck->setTruckParkingArea(nullptr);
        truck = nullptr;
        return true;
    }
    return false;
}

int TruckParkingArea::getId(){
    std::lock_guard<std::mutex> lock(mutex);
    return id;
}

bool TruckParkingArea::isAvailable(){
    std::lock_guard<std::mutex> lock(mutex);
    return available;
}

Truck *TruckParkingArea::getTruck(){
    std::lock_guard<std::mutex> lock(mutex);
    return truck;
}
