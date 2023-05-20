//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_SEAPORT_H
#define SEAPORT_SO2_SEAPORT_H

#include <vector>
#include "view/IView.h"
#include "view/ConsoleView.h"
#include "view/NcursesView.h"
#include "stoppingPlaces/Dock.h"
#include "stoppingPlaces/TruckParkingArea.h"
#include "vehicles/Ship.h"
#include "vehicles/Truck.h"


class Seaport {
    IView* view;
    std::vector<Dock> Docks;
    std::vector<TruckParkingArea> truckParkingAreas;
    std::vector<Ship> ships;
    std::vector<Truck> trucks;
    std::mutex mutex;

public:
    Seaport();
    virtual ~Seaport();
    void startWorking();

private:
    bool initializeView();
    bool exitView();

};


#endif //SEAPORT_SO2_SEAPORT_H
