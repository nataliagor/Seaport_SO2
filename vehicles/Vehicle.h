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
    bool statusChanged;

    std::mutex loadStatusMutex;
    std::mutex loadInLitersMutex;
    std::mutex timeInPortMutex;
    std::mutex maxTimeInPortMutex;
    std::mutex statusChangedMutex;

public:
    Vehicle(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort);
    ~Vehicle();
    bool isEmpty();
    bool isLoaded();
    bool isBeingLoaded();
    bool isBeingUnloaded();
    bool isFull();

    int unload(int amount) ;
    int load(int amount) ;

    int getTimeInPort();
    int getMaxTimeInPort();
    int getTimeInPortLeft();
    int getId() const;
    int getCapacityInLitres() const;
    int getLoadInLiters();;

    LoadStatus getLoadStatus();
    void setLoadStatus(LoadStatus loadStatus);

    void setLoadInLiters(int loadInLiters);

    bool isStatusChanged();
    void setStatusChanged(bool statusChanged);
};


#endif //SEAPORT_SO2_VEHICLE_H
