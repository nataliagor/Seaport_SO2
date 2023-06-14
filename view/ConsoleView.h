//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_CONSOLEVIEW_H
#define SEAPORT_SO2_CONSOLEVIEW_H

#include "IView.h"
#include <iostream>
#include <mutex>

class ConsoleView : public IView{
    std::mutex mutex;
public:
    ConsoleView();
    virtual ~ConsoleView();

    bool exitView() override;
    void test(std::string test) override;

    void newShipAppears(int shipId, int capacityInLitres, int loadInLiters, int maxTimeInPort) override;
    void freeDock(int dockId) override;
    void occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters) override;

    void newTruckAppears(int truckId, int capacityInLitres, int loadInLiters, int maxTimeInPort) override;
    void freeTruckParkingArea(int truckParkingAreaId) override;
    void occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters) override;

    void reloadTruckToShip(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) override;
    void reloadShipToTruck(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) override;

    void showShipsQueue(int shipId, int maxTimeInPort, int timeInPort, bool newQueue) override;
    void showTruckQueue(int truckId, int maxTimeInPort, int timeInPort, bool newQueue) override;

private:
};


#endif //SEAPORT_SO2_CONSOLEVIEW_H
