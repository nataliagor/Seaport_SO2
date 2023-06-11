//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_IVIEW_H
#define SEAPORT_SO2_IVIEW_H

#include <string>
#include "../vehicles/LoadStatus.h"

class IView {
public:
    virtual bool exitView() = 0;
    virtual void test(std::string test) = 0;

    virtual void newShipAppears(int shipId, int capacityInLitres, int loadInLiters) = 0;
    virtual void freeDock(int dockId) = 0;
    virtual void occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters) = 0;

    virtual void newTruckAppears(int truckId, int capacityInLitres, int loadInLiters) = 0;
    virtual void freeTruckParkingArea(int TruckParkingAreaId) = 0;
    virtual void occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters) = 0;

    virtual void reloadTruckToShip(int shipId, int truckId, int amount) = 0;
    virtual void reloadShipToTruck(int shipId, int truckId, int amount) = 0;

};


#endif //SEAPORT_SO2_IVIEW_H
