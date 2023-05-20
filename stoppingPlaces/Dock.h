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
    std::mutex mutex;

};


#endif //SEAPORT_SO2_DOCK_H
