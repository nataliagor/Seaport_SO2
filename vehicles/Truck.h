//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_TRUCK_H
#define SEAPORT_SO2_TRUCK_H

#include "Vehicle.h"

class TruckParkingArea;   // Forward declaration

class Truck : public Vehicle{
    TruckParkingArea* truckParkingArea;

public:
    Truck();
    ~Truck();

};


#endif //SEAPORT_SO2_TRUCK_H
