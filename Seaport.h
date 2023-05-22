//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_SEAPORT_H
#define SEAPORT_SO2_SEAPORT_H

#include <vector>
#include <queue>
#include <thread>
#include <random>
#include "view/IView.h"
#include "view/ConsoleView.h"
#include "view/NcursesView.h"
#include "stoppingPlaces/Dock.h"
#include "stoppingPlaces/TruckParkingArea.h"
#include "vehicles/Ship.h"
#include "vehicles/Truck.h"
#include "PortAdministrator.h"

constexpr int NUMBER_OF_DOCKS = 5;

class Seaport {
    IView* view;
    int numberOfDocks;
    std::vector<Dock*> docks;                                           //współdielony przez administratora (szukanie pustych, zmiana na zajety) i statki (zmiana na wolny)
    std::vector<TruckParkingArea*> truckParkingAreas;                   //współdzielony przez administratora (szukanie pustych, zmiana na zajety) i ciężarówki (zmiana na wolny)

    int numberOfEmptyTrucks;                                            //współdzielony przez daministrator i ciężaróki
    int numberOfEmptyShips;                                             //współdzielony przez daministrator i statki
    int numberOfLoadedTrucks;                                           //współdzielony przez daministrator i ciężaróki
    int numberOfLoadedShips;                                            //współdzielony przez daministrator i statki

    int lastShipId;                                                     //statki
    int lastTruckId;                                                    //statki

    std::vector<std::thread> shipsThreads;
    std::vector<std::thread> trucksThreads;
    std::thread adminThread;

    std::mutex shipIdMutex;
    std::mutex truckIdMutex;
    std::mutex randMutex;
    std::mutex emptyShipsMutex;
    std::mutex loadedShipsMutex;
    std::mutex emptyTrucksMutex;
    std::mutex loadedTrucksMutex;
    std::mutex docksAndParkingAreasMutex;

    std::random_device rd;
    PortAdministrator* portAdministrator;

public:
    Seaport(int numberOfDocks);
    virtual ~Seaport();
    void startWorking();

private:
    bool initializeView();
    bool exitView();
    int getRandomNumb(int min, int max);

    void administratorLife();
    void giveLeavePermissions();
    void giveDockPermissions();
    bool checkIfEmptyShipIsNeeded(Dock* dock);
    void dockShip(Dock* dock);
    void giveParkPermissions();
    bool checkIfEmptyTruckIsNeeded(TruckParkingArea* truckParkingAreas);
    void parkTruck(TruckParkingArea* truckParkingArea);

    void shipLife();
    Ship* newShipAppears();
    void enterPort(Ship* ship);
    void addShipToWaitingQueue(Ship *ship);
    void leavePort(Ship* ship);
    bool unloadShip(Ship* ship);

    void trucksLife();
    Truck* newTruckAppears();
    void enterPort(Truck* truck);
    void addTruckToWaitingQueue(Truck* truck);
    void leavePort(Truck* truck);
    bool unloadTruck(Truck* truck);


public:
    int getNumberOfEmptyTrucks();
    void setNumberOfEmptyTrucks(int numberOfEmptyTrucks);
    int getNumberOfEmptyShips();
    void setNumberOfEmptyShips(int numberOfEmptyShips);
    int getNumberOfLoadedTrucks();
    void setNumberOfLoadedTrucks(int numberOfLoadedTrucks);
    int getNumberOfLoadedShips();
    void setNumberOfLoadedShips(int numberOfLoadedShips);

};


#endif //SEAPORT_SO2_SEAPORT_H
