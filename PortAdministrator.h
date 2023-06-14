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


struct CompareShipsByTimeLeft {
    bool operator()(Ship* ship1, Ship* ship2) const {
        return ship1->getLeftTimeInPort() > ship2->getLeftTimeInPort();
    }
};

struct CompareTrucksByTimeLeft {
    bool operator()(Truck* truck1, Truck* truck2) const {
        return truck1->getLeftTimeInPort() > truck2->getLeftTimeInPort();
    }
};

class PortAdministrator {
    std::priority_queue<Ship*, std::vector<Ship*>, CompareShipsByTimeLeft> emptyShipsToDockPriorityQueue;
    std::priority_queue<Ship*, std::vector<Ship*>, CompareShipsByTimeLeft>loadedShipsToDockPriorityQueue;
    std::priority_queue<Ship*, std::vector<Ship*>, CompareShipsByTimeLeft> loadedShipsToLeavePriorityQueue;
    std::priority_queue<Ship*, std::vector<Ship*>, CompareShipsByTimeLeft>emptyShipsToLeavePriorityQueue;
    std::mutex emptyShipsQueueMutex;
    std::mutex loadedShipsQueueMutex;
    std::mutex loadedLeavingShipsQueueMutex;
    std::mutex emptyLeavingShipsQueueMutex;

    std::priority_queue<Truck*, std::vector<Truck*>, CompareTrucksByTimeLeft> emptyTrucksToParkPriorityQueue;
    std::priority_queue<Truck*, std::vector<Truck*>, CompareTrucksByTimeLeft>  loadedTrucksToParkPriorityQueue;
    std::priority_queue<Truck*, std::vector<Truck*>, CompareTrucksByTimeLeft>  loadedTrucksToLeavePriorityQueue;
    std::priority_queue<Truck*, std::vector<Truck*>, CompareTrucksByTimeLeft>  emptyTrucksToLeavePriorityQueue;
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
