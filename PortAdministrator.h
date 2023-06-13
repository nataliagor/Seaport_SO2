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
    std::priority_queue<Ship*> loadedShipsToLeavePriorityQueue;
    std::priority_queue<Ship*> emptyShipsToLeavePriorityQueue;
    std::mutex emptyShipsQueueMutex;
    std::mutex loadedShipsQueueMutex;
    std::mutex loadedLeavingShipsQueueMutex;
    std::mutex emptyLeavingShipsQueueMutex;

    std::priority_queue<Truck*> emptyTrucksToParkPriorityQueue;
    std::priority_queue<Truck*> loadedTrucksToParkPriorityQueue;
    std::priority_queue<Truck*> loadedTrucksToLeavePriorityQueue;
    std::priority_queue<Truck*> emptyTrucksToLeavePriorityQueue;
    std::mutex emptyTrucksQueueMutex;
    std::mutex loadedTrucksQueueMutex;
    std::mutex loadedLeavingTrucksQueueMutex;
    std::mutex emptyLeavingTrucksQueueMutex;

    IView& view;

public:
    explicit PortAdministrator(IView &view);
    virtual ~PortAdministrator();

    void addToEmptyShipsToDockQueue(Ship* ship);
    void addToLoadedShipsToDockQueue(Ship* ship);
    void addToLoadedShipsToLeaveQueue(Ship* ship);
    void addToEmptyShipsToLeaveQueue(Ship* ship);

    bool givePermissionToLoadedToDock(Dock* dock);
    bool givePermissionToEmptyToDock(Dock* dock);
    int giveLoadedPermissionsToLeaveDock(int numberOfLoadedShips);
    int giveEmptyPermissionsToLeaveDock(int numberOfEmptyShips);

    void addToEmptyTrucksToParkQueue(Truck* truck);
    void addToLoadedTrucksToParkQueue(Truck* truck);
    void addToLoadedTrucksToLeaveQueue(Truck* truck);
    void addToEmptyTrucksToLeaveQueue(Truck* truck);

    bool givePermissionToLoadedToPark(TruckParkingArea* truckParkingArea);
    bool givePermissionToEmptyToPark(TruckParkingArea* truckParkingArea);
    int giveLoadedPermissionsToLeaveParking(int numberOfLoadedTrucks);
    int giveEmptyPermissionsToLeaveParking(int numberOfEmptyTrucks);

};


#endif //SEAPORT_SO2_PORTADMINISTRATOR_H
