//
// Created by natalia on 18.05.23.
//

#include "NcursesView.h"
#include <ncurses.h>

NcursesView::NcursesView() {
    initscr();
    printw("Welcome in seaPort");
    refresh();
    getch();
}

NcursesView::~NcursesView() {

}

bool NcursesView::exitView(){
    endwin();
    return true;
}

void NcursesView::test(std::string test) {

}

void NcursesView::newShipAppears(int shipId, int capacityInLitres, int loadInLiters) {

}

void NcursesView::freeDock(int dockId){

}

void NcursesView::occupyDock(int dockId, int shipId) {

}

void NcursesView::newTruckAppears(int truckId, int capacityInLitres, int loadInLiters) {

}

void NcursesView::freeTruckParkingArea(int truckParkingAreaId) {

}

void NcursesView::occupyTruckParkingArea(int truckParkingAreaId, int truckId) {

}

void NcursesView::reloadTruckToShip(int shipId, int truckId, int amount) {

}

void NcursesView::reloadShipToTruck(int shipId, int truckId, int amount) {

}
