//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_IVIEW_H
#define SEAPORT_SO2_IVIEW_H

#include <string>
#include <queue>
#include "../vehicles/LoadStatus.h"
#include "../vehicles/Vehicle.h"
#include "../vehicles/Ship.h"
#include "../vehicles/Truck.h"

class IView {
public:
    virtual bool exitView() = 0;
    virtual void test(std::string test) = 0;

    virtual void newShipAppears(int shipId, int capacityInLitres, int loadInLiters, int maxTimeInPort) = 0;
    virtual void freeDock(int dockId) = 0;
    virtual void occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters) = 0;

    virtual void newTruckAppears(int truckId, int capacityInLitres, int loadInLiters, int maxTimeInPort) = 0;
    virtual void freeTruckParkingArea(int TruckParkingAreaId) = 0;
    virtual void occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters) = 0;

    virtual void reloadTruckToShip(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) = 0;
    virtual void reloadShipToTruck(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) = 0;

    virtual void showShipsQueue(int shipId, int maxTimeInPort, int timeInPort, bool newQueue) = 0;
    virtual void showTruckQueue(int truckId, int maxTimeInPort, int timeInPort, bool newQueue) = 0;

};


#endif //SEAPORT_SO2_IVIEW_H
