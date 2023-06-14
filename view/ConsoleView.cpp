//
// Created by natalia on 18.05.23.
//

#include "ConsoleView.h"

ConsoleView::ConsoleView() {
    std::cout << "Witaj w porcie!" << std::endl;
}

ConsoleView::~ConsoleView() {}

bool ConsoleView::exitView(){
    std::cout << "Zegnaj!" << std::endl;
    return true;
}

void ConsoleView::test(std::string test){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "TEST: " << test << std::endl;
}

void ConsoleView::newShipAppears(int shipId, int capacityInLitres, int loadInLiters, int maxTimeInPort){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Statek " << shipId << " pojemnosc: " << capacityInLitres << " ladunek: " << loadInLiters <<std::endl;
}

void ConsoleView::freeDock(int dockId){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Miejsce do cumowania " << dockId << " zostalo zwolnione" << std::endl;
}

void ConsoleView::occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Miejsce do cumowania " << dockId << " zostalo zajete przez statek " <<  shipId << std::endl;
}

void ConsoleView::newTruckAppears(int truckId, int capacityInLitres, int loadInLiters, int maxTimeInPort){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Ciezarowka " << truckId << " pojemnosc: " << capacityInLitres << " ladunek: " << loadInLiters << std::endl;
}

void ConsoleView::freeTruckParkingArea(int truckParkingAreaId){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Miejsce prakingowe " << truckParkingAreaId << " zostalo zwolnione" << std::endl;
}

void ConsoleView::occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Miejsce parkingowe " << truckParkingAreaId << " zostalo zajete przez ciezarowke " <<  truckId << std::endl;
}


void ConsoleView::reloadTruckToShip(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Przeladowanie " << amount << " litrow z ciezarowki " << truckId << " do statku " <<  shipId << std::endl;
}

void ConsoleView::reloadShipToTruck(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Przeladowanie " << amount << " litrow z statku " << shipId << " do ciezarowki " <<  truckId << std::endl;
}

void ConsoleView::showShipsQueue(int shipId, int maxTimeInPort, int timeInPort, bool newQueue) {

}

void ConsoleView::showTruckQueue(int truckId, int maxTimeInPort, int timeInPort, bool newQueue) {

}


