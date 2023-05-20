//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_VEHICLE_H
#define SEAPORT_SO2_VEHICLE_H

#include "LoadStatus.h"

class Vehicle {

protected:
    int id;
    int capacityInLitres;
    int loadInLiters;
    LoadStatus loadStatus;
    int timeInPort;
    int maxTimeInPort;

public:
    Vehicle();
    ~Vehicle();
    bool unload(int amount);
    bool load(int amount);
    bool isEmpty();
    bool isLoaded();
    bool isFull() const;

};


#endif //SEAPORT_SO2_VEHICLE_H
