//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_VEHICLE_H
#define SEAPORT_SO2_VEHICLE_H

#include <mutex>
#include "LoadStatus.h"

class Vehicle {

protected:
    int id;
    int capacityInLitres;
    int loadInLiters;
    LoadStatus loadStatus;
    int timeInPort;
    int maxTimeInPort;
    std::mutex loadStatusMutex;

public:
    Vehicle(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort);
    ~Vehicle();
    bool isEmpty();
    bool isLoaded();
    bool isFull();

    int unload(int amount) ;
    int load(int amount) ;
    int getTimeInPort();
    int getMaxTimeInPort();
    int getTimeInPortLeft();

};


#endif //SEAPORT_SO2_VEHICLE_H
