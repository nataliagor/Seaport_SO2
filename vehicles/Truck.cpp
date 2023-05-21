//
// Created by natalia on 18.05.23.
//

#include "Truck.h"
#include "../stoppingPlaces/TruckParkingArea.h"

Truck::Truck(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort) : Vehicle(id, capacityInLitres, loadInLiters, maxTimeInPort) {
    truckParkingArea = nullptr;
}

Truck::~Truck() {}

bool Truck::leaveSeaport(){
    if(truckParkingArea != nullptr){
        truckParkingArea->freeParkingArea();            //? czy tutaj dodac pytanie do aministrator i on zwalnia miejsce
        truckParkingArea = nullptr;
        return true;
    }
    return false;
}

TruckParkingArea *Truck::getTruckParkingArea() const {
    return truckParkingArea;
}

void Truck::setTruckParkingArea(TruckParkingArea *truckParkingArea) {
    Truck::truckParkingArea = truckParkingArea;
}
