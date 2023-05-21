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



class PortAdministrator {
    std::priority_queue<Ship*> emptyShipsToDockPriorityQueue;
    std::priority_queue<Ship*> loadedShipsToDockPriorityQueue;
    std::priority_queue<Ship*> shipsToLeavePriorityQueue;                       //opuszczją tylko loaded
    std::mutex emptyShipsQueueMutex;
    std::mutex loadedShipsQueueMutex;
    std::mutex leavingShipsQueueMutex;
public:
    PortAdministrator();
    virtual ~PortAdministrator();

    void addToEmptyShipsToDockQueue(Ship* ship);
    void addToLoadedShipsToDockQueue(Ship* ship);
    void addToShipsToLeaveQueue(Ship* ship);

    void givePermissionToLoadedToDock(Dock* dock);
    void givePermissionToEmptyToDock(Dock* dock);
    int givePermissionsToLeaveDock(int numberOfLoadedShips);

    TruckParkingArea getPermissionToPark(Truck* truck);
    bool getPermissionToLeavePort(Truck* truck);

};


#endif //SEAPORT_SO2_PORTADMINISTRATOR_H
