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

private:
    int id;
    bool available;
    Truck* truck;
    //std::vector<Truck*> trucks;
    std::mutex idMutex;
    std::mutex availableMutex;
    std::mutex truckMutex;

public:
    TruckParkingArea(int id);
    virtual ~TruckParkingArea();
    bool occupyParkingArea(Truck *newTruck);
    bool freeParkingArea();

    int getId();
    bool isAvailable();
    Truck *getTruck();

    void setAvailable(bool available);

};


#endif //SEAPORT_SO2_TRUCKPARKINGAREA_H
