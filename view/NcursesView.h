//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_NCURSESVIEW_H
#define SEAPORT_SO2_NCURSESVIEW_H

#include <mutex>
#include "IView.h"

class NcursesView : public IView{
    std::mutex mutex;
public:
    NcursesView();
    virtual ~NcursesView();

    bool exitView() override;
    void test(std::string test) override;

    void newShipAppears(int shipId, int capacityInLitres, int loadInLiters) override;
    void freeDock(int dockId) override;
    void occupyDock(int dockId, int shipId) override;

    void newTruckAppears(int truckId, int capacityInLitres, int loadInLiters) override;
    void freeTruckParkingArea(int truckParkingAreaId) override;
    void occupyTruckParkingArea(int truckParkingAreaId, int truckId) override;

    void reloadTruckToShip(int shipId, int truckId, int amount) override;
    void reloadShipToTruck(int shipId, int truckId, int amount) override;
};


#endif //SEAPORT_SO2_NCURSESVIEW_H
