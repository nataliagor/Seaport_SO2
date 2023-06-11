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

class NcursesView : public IView{
    int numberOfDocks;
    std::mutex mutex;

    int lastShipPosInQueue;
    int lastTruckPosInQueue;
    int lastPanelInfoPos;

public:
    NcursesView(int numberOfDocks);
    virtual ~NcursesView();

    bool exitView() override;
    void test(std::string test) override;

    void newShipAppears(int shipId, int capacityInLitres, int loadInLiters) override;
    void freeDock(int dockId) override;
    void occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters) override;

    void newTruckAppears(int truckId, int capacityInLitres, int loadInLiters) override;
    void freeTruckParkingArea(int truckParkingAreaId) override;
    void occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters) override;

    void reloadTruckToShip(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) override;
    void reloadShipToTruck(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) override;

private:
    void welcomeMessage();
    void initializeColors();

    void drawStartView();
    void writeHeadlines(int docksXPosition, int parkingAreasXPosition);
    void vehiclesParametersHeadlines(int yPosition, int xPosition, bool drawLines);
    void drawDockAndParkingAreas(int headlineSpace, int docksXPosition, int parkingAreasXPosition);
    void drawSquares(int startXPosition, int headlineSpace, bool textOnTheRight);

    void drawSquare(int yPosition, int xPosition);
    void drawVerticalLine(int yPosition, int xPosition, int length, char symbol);
    void drawHorizontalLine(int yPosition, int xPosition, int length, char symbol);

};


#endif //SEAPORT_SO2_NCURSESVIEW_H
