//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_PORTADMINISTRATOR_H
#define SEAPORT_SO2_PORTADMINISTRATOR_H

#include <queue>
#include "stoppingPlaces/Dock.h"
#include "stoppingPlaces/TruckParkingArea.h"
#include "vehicles/Ship.h"
#include "vehicles/Truck.h"
#include "view/IView.h"


class PortAdministrator {
    std::priority_queue<Ship*> emptyShipsToDockPriorityQueue;                   //segragecja czasem //TODO
    std::priority_queue<Ship*> loadedShipsToDockPriorityQueue;
    std::priority_queue<Ship*> shipsToLeavePriorityQueue;                       //opuszczją tylko loaded
    std::mutex emptyShipsQueueMutex;
    std::mutex loadedShipsQueueMutex;
    std::mutex leavingShipsQueueMutex;

    std::priority_queue<Truck*> emptyTrucksToParkPriorityQueue;
    std::priority_queue<Truck*> loadedTrucksToParkPriorityQueue;
    std::priority_queue<Truck*> trucksToLeavePriorityQueue;                       //opuszczją tylko loaded
    std::mutex emptyTrucksQueueMutex;
    std::mutex loadedTrucksQueueMutex;
    std::mutex leavingTrucksQueueMutex;

    IView& view;

public:
    explicit PortAdministrator(IView &view);
    virtual ~PortAdministrator();

    void addToEmptyShipsToDockQueue(Ship* ship);
    void addToLoadedShipsToDockQueue(Ship* ship);
    void addToShipsToLeaveQueue(Ship* ship);

    bool givePermissionToLoadedToDock(Dock* dock);
    bool givePermissionToEmptyToDock(Dock* dock);
    int givePermissionsToLeaveDock(int numberOfLoadedShips);

    void addToEmptyTrucksToParkQueue(Truck* truck);
    void addToLoadedTrucksToParkQueue(Truck* truck);
    void addToTrucksToLeaveQueue(Truck* truck);

    bool givePermissionToLoadedToPark(TruckParkingArea* truckParkingArea);
    bool givePermissionToEmptyToPark(TruckParkingArea* truckParkingArea);
    int givePermissionsToLeaveParking(int numberOfLoadedTrucks);

};


#endif //SEAPORT_SO2_PORTADMINISTRATOR_H
