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
    std::mutex statusChangedMutex;

public:
    Vehicle(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort);
    virtual ~Vehicle();
    bool isEmpty();
    bool isLoaded();
    bool isBeingLoaded();
    bool isBeingUnloaded();
    bool isFull();

    int unload(int amount) ;
    int load(int amount) ;

    int getId() const;
    int getCapacityInLitres() const;
    int getLoadInLiters();;
    void setLoadInLiters(int loadInLiters);

    LoadStatus getLoadStatus();
    void setLoadStatus(LoadStatus loadStatus);
    bool isStatusChanged();
    void setStatusChanged(bool statusChanged);

    void setTimeInPort(int timeInPort);
    int getTimeInPort();
    int getMaxTimeInPort();
    int getTimeInPortLeft();
    int getLeftTimeInPort();
};


#endif //SEAPORT_SO2_VEHICLE_H
