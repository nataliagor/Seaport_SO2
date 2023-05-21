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
    if(!available){
        available = true;
        truck = nullptr;
        return true;
    }
    return false;
}
