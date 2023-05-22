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

    void newShipAppears(int shipId) override;
    void freeDock(int dockId) override;
    void occupyDock(int dockId, int shipId) override;

    void newTruckAppears(int truckId) override;
    void freeTruckParkingArea(int truckParkingAreaId) override;
    void occupyTruckParkingArea(int truckParkingAreaId, int truckId) override;

private:
};


#endif //SEAPORT_SO2_CONSOLEVIEW_H
