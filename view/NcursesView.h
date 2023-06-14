//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_NCURSESVIEW_H
#define SEAPORT_SO2_NCURSESVIEW_H

#include <mutex>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include "IView.h"
#include "../vehicles/Ship.h"
#include "../vehicles/Truck.h"

class NcursesView : public IView{
    int numberOfDocks;
    std::mutex mutex;

    int lastShipPosInList;
    int lastTruckPosInList;
    int lastPanelInfoPos;

    int lastShipPosInQueue;
    int lastTruckPosInQueue;

public:
    NcursesView(int numberOfDocks);
    virtual ~NcursesView();

    bool exitView() override;
    void test(std::string test) override;

    void newShipAppears(int shipId, int capacityInLitres, int loadInLiters, int maxTimeInPort) override;
    void freeDock(int dockId) override;
    void occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters) override;

    void newTruckAppears(int truckId, int capacityInLitres, int loadInLiters, int maxTimeInPort) override;
    void freeTruckParkingArea(int truckParkingAreaId) override;
    void occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters) override;

    void reloadTruckToShip(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) override;
    void reloadShipToTruck(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) override;

    void showShipsQueue(int shipId, int maxTimeInPort, int timeInPort, bool newQueue) override;
    void showTruckQueue(int truckId, int maxTimeInPort, int timeInPort, bool newQueue) override;

private:
    void welcomeMessage();
    void initializeColors();

    void drawStartView();
    void writeHeadlines(int docksXPosition, int parkingAreasXPosition);
    void vehiclesParametersHeadlines(int yPosition, int xPosition, bool drawLines);
    void vehiclesTimeInPortHeadlines(int yPosition, int xPosition, bool drawLines);
    void drawDockAndParkingAreas(int headlineSpace, int docksXPosition, int parkingAreasXPosition);
    void drawSquares(int startXPosition, int headlineSpace, bool textOnTheRight);

    void drawSquare(int yPosition, int xPosition);
    void drawVerticalLine(int yPosition, int xPosition, int length, char symbol);
    void drawHorizontalLine(int yPosition, int xPosition, int length, char symbol);

    void cleanQueue(int firstY, int firstX);
};


#endif //SEAPORT_SO2_NCURSESVIEW_H
