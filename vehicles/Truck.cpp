//
// Created by natalia on 18.05.23.
//

#include "Truck.h"
#include "../stoppingPlaces/TruckParkingArea.h"

Truck::Truck(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : Vehicle(id, capacityInLitres, loadInLiters, maxTimeInPort) {
    truckParkingArea = nullptr;
    timeInPort = 0;     //tutaj zaczac odliczanie czasu //TODO
}

Truck::~Truck() {}

bool Truck::leaveSeaport(){
    std::lock_guard<std::mutex> lock(parkingAreaMutex);
    if(truckParkingArea != nullptr){
        truckParkingArea->freeParkingArea();
        truckParkingArea = nullptr;
        return true;
    }
    return false;
}

TruckParkingArea *Truck::getTruckParkingArea(){
    std::lock_guard<std::mutex> lock(parkingAreaMutex);
    return truckParkingArea;
}

void Truck::setTruckParkingArea(TruckParkingArea *truckParkingArea) {
    std::lock_guard<std::mutex> lock(parkingAreaMutex);
    Truck::truckParkingArea = truckParkingArea;
}
