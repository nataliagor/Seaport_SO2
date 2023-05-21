//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_SHIP_H
#define SEAPORT_SO2_SHIP_H

#include <mutex>
#include "Vehicle.h"

class Dock;  // Forward declaration

class Ship : public Vehicle{
    Dock* dock;
    std::mutex dockMutex;

public:
    Ship(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort);
    ~Ship();
    bool leaveSeaport();
    void setDock(Dock *dock);
    Dock *getDock();
};


#endif //SEAPORT_SO2_SHIP_H
