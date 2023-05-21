//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_SEAPORT_H
#define SEAPORT_SO2_SEAPORT_H

#include <vector>
#include <queue>
#include <thread>
#include "view/IView.h"
#include "view/ConsoleView.h"
#include "view/NcursesView.h"
#include "stoppingPlaces/Dock.h"
#include "stoppingPlaces/TruckParkingArea.h"
#include "vehicles/Ship.h"
#include "vehicles/Truck.h"

constexpr int NUMBER_OF_DOCKS = 5;

class Seaport {
    IView* view;
    int numberOfDocks;
    std::vector<Dock*> docks;                                           //współdielony przez administratora (szukanie pustych, zmiana na zajety) i statki (zmiana na wolny)
    std::vector<TruckParkingArea*> truckParkingAreas;                   //współdzielony przez administratora (szukanie pustych, zmiana na zajety) i ciężarówki (zmiana na wolny)
    std::queue<Ship*> shipsQueue;                                       //kolejka nowych statków oczekujących na wpłynięcie do portu //administrator i watek główny
    std::queue<Truck*> trucksQueue;                                     //kolejka nowych ciężarówek oczekującyh na wjazd do portu    //administrator i wątek główny
    int numberOfEmptyTrucks;                                            //współdzielony przez daministrator i ciężaróki
    int numberOfEmptyShips;                                             //współdzielony przez daministrator i statki
    int numberOfLoadedTrucks;                                           //współdzielony przez daministrator i ciężaróki
    int numberOfLoadedShips;                                            //współdzielony przez daministrator i statki
    int lastShipId;                                                     //statki
    int lastTruckId;                                                    //statki
    std::vector<std::thread> shipsThreads;
    std::vector<std::thread> trucksThreads;
    std::mutex mutex;


public:
    Seaport(int numberOfDocks);
    virtual ~Seaport();
    void startWorking();

private:
    bool initializeView();
    bool exitView();
    Ship* newShipAppears();
    void newTruckAppears();

};


#endif //SEAPORT_SO2_SEAPORT_H
