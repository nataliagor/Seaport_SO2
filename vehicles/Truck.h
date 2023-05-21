//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_TRUCK_H
#define SEAPORT_SO2_TRUCK_H

#include "Vehicle.h"

class TruckParkingArea;   // Forward declaration

class Truck : public Vehicle{
    TruckParkingArea *truckParkingArea;

public:
    Truck(int id, int capacityInLitres, int loadInLiters, int maxTimeInPort);
    ~Truck();
    bool leaveSeaport();
    void setTruckParkingArea(TruckParkingArea *truckParkingArea);
    TruckParkingArea *getTruckParkingArea() const;

};


#endif //SEAPORT_SO2_TRUCK_H
