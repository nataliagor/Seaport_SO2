//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_SEAPORT_H
#define SEAPORT_SO2_SEAPORT_H

#include <vector>
#include <queue>
#include <thread>
#include <random>
//#include <windows.h>
#include <unistd.h>
#include <typeinfo>
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

    std::mutex lastShipIdMutex;
    std::mutex lastTruckIdMutex;
    std::mutex randMutex;
    std::mutex emptyShipsMutex;
    std::mutex loadedShipsMutex;
    std::mutex emptyTrucksMutex;
    std::mutex loadedTrucksMutex;
    std::mutex docksMutex;                  //te dwa polaczyc
    std::mutex parkingAreasMutex;           //jakby sie cos psulo
    std::mutex reloadingMutex;

    std::random_device rd;
    PortAdministrator* portAdministrator;

    std::vector<Ship*> ships;
    std::vector<Truck*> trucks;
    std::mutex shipsMutex;
    std::mutex trucksMutex;

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
    bool reloadShip(Ship* ship);

    bool reloadTruckToShip(Ship *ship, Truck* truck);
    bool reloadShipToTruck(Ship *ship, Truck* truck);

    void trucksLife();
    Truck* newTruckAppears();
    void enterPort(Truck* truck);
    void addTruckToWaitingQueue(Truck* truck);
    void leavePort(Truck* truck);
    bool reloadTruck(Truck* truck);


    int getNumberOfEmptyTrucks();
    void setNumberOfEmptyTrucks(int numberOfEmptyTrucks);
    int getNumberOfEmptyShips();
    void setNumberOfEmptyShips(int numberOfEmptyShips);
    int getNumberOfLoadedTrucks();
    void setNumberOfLoadedTrucks(int numberOfLoadedTrucks);
    int getNumberOfLoadedShips();
    void setNumberOfLoadedShips(int numberOfLoadedShips);
    int getCurrentShipId();
    int getCurrentTruckId();

    std::vector<Dock *> &getDocks();
    std::vector<TruckParkingArea *> &getTruckParkingAreas();
    Dock* getDockById(int id);
    TruckParkingArea* getTruckParkingAreaById(int id);

    void addShipToShipsVector(Ship* ship);
    void addTruckToTrucksVector(Truck* truck);
    void deleteShipFromShipsVector(Ship* ship);
    void deleteTruckFromTrucksVector(Truck* truck);
    void actualizeShipsTime();
    void actualizeTrucksTime();

};


#endif //SEAPORT_SO2_SEAPORT_H
