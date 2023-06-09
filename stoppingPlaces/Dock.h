//
// Created by dell on 19.05.2023.
//

#ifndef SEAPORT_SO2_DOCK_H
#define SEAPORT_SO2_DOCK_H


#include <mutex>

class Ship;  // Forward declaration

class Dock {
    int id;
    bool available;
    Ship* ship;
    std::mutex idMutex;
    std::mutex availableMutex;
    std::mutex shipMutex;

public:
    explicit Dock(int id);
    virtual ~Dock();
    bool occupyDock(Ship *newShip);
    bool freeDock();

    int getId();
    bool isAvailable();
    Ship *getShip();

private:
    void setAvailable(bool available);
};


#endif //SEAPORT_SO2_DOCK_H
