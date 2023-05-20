//
// Created by dell on 19.05.2023.
//

#ifndef SEAPORT_SO2_TRUCKPARKINGAREA_H
#define SEAPORT_SO2_TRUCKPARKINGAREA_H


#include <mutex>
#include <vector>

class Truck;   // Forward declaration
//constexpr int MAX_NUMBER_OF_TRUCKS = 3;

class TruckParkingArea {
    int id;
    bool available;
    Truck* truck;
    //std::vector<Truck*> trucks;
    std::mutex mutex;

};


#endif //SEAPORT_SO2_TRUCKPARKINGAREA_H
