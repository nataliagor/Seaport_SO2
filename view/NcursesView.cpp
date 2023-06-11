//
// Created by natalia on 18.05.23.
//

#include "NcursesView.h"



NcursesView::NcursesView(int numberOfDocks) : numberOfDocks(numberOfDocks), lastShipPosInQueue(0) , lastTruckPosInQueue(0), lastPanelInfoPos(0) {
    initscr();
    initializeColors();

    welcomeMessage();
    drawStartView();
}

NcursesView::~NcursesView() {}


void NcursesView::welcomeMessage(){
    bkgd(COLOR_PAIR(1));
    attron(A_BOLD);
    attron(COLOR_PAIR(1));

    mvprintw(3,60, "Witaj w porcie!");
    mvprintw(6,60, "Kliknij dowolny klawisz by kontynulowac");

    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
    refresh();

    noecho();
    while (int esc=getch() == ERR){}

    mvprintw(3,60, "                   ");
    mvprintw(6,60, "                                       ");
    refresh();
}

void NcursesView::initializeColors(){
    start_color();
    init_pair(0,COLOR_BLACK,COLOR_BLUE);
    init_pair(1,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(3,COLOR_BLACK,COLOR_GREEN);
    init_pair(4,COLOR_BLACK,COLOR_CYAN);
    init_pair(5,COLOR_BLACK,COLOR_RED);
    init_pair(6,COLOR_BLACK,COLOR_YELLOW);
}


//-------------------------------background-------------------------------
void NcursesView::drawStartView(){
    int headlineSpace = 5;
    int docksXPosition = 10;
    int parkingAreasXPosition = 25;

    bkgd(COLOR_PAIR(4));
    writeHeadlines(docksXPosition, parkingAreasXPosition);
    drawDockAndParkingAreas(headlineSpace, docksXPosition, parkingAreasXPosition);
    refresh();
}

void NcursesView::writeHeadlines(int docksXPosition, int parkingAreasXPosition){
    bkgdset(COLOR_PAIR(4));

    attron(A_BOLD);
    mvprintw(0, docksXPosition - 3, "Miejsca do");                                //dock y = 0, x = 10, headline = 5
    mvprintw(1, docksXPosition - 3, "cumowania");

    mvprintw(0, parkingAreasXPosition - 3 , "Miejsca do");                       //parking area y = 0, x = 25, headline = 5
    mvprintw(1, parkingAreasXPosition - 3 , "prakowania");

    mvprintw(0, 47, "Informacje o statku i ciezarowce");                         //info y = 0, x = 47, headline = 5
    mvprintw(0, 95, "Panel informacyjny");                                       //panel y = 0, x = 95, headline = 5

    mvprintw(21, 95, "Kolejka oczekujacych statkow");                            //kolejka statkow y = 21, x = 95, headline = 5
    mvprintw(21, 140, "Kolejka oczekujacych ciezarowek");                       //kolejka ciezarowek y = 21, x = 140
    attroff(A_BOLD);

    drawHorizontalLine(19, 91, 200, '_');
    drawVerticalLine( 0, 90, 60, '|');

    vehiclesParametersHeadlines(23, 95, true);      //kolejka statkow
    vehiclesParametersHeadlines(23, 140, true);     //kolejka ciezarowek
    vehiclesParametersHeadlines(2, 47, false);     //informacje przy dockach i parkingach

}

void NcursesView::vehiclesParametersHeadlines(int yPosition, int xPosition, bool drawLines){
    mvprintw(yPosition, xPosition, "Nr");
    mvprintw(yPosition, xPosition + 6, "Ladownosc");
    mvprintw(yPosition + 1, xPosition + 6, "[l]");
    mvprintw(yPosition, xPosition + 16, "Ladunek");
    mvprintw(yPosition + 1, xPosition + 16, "[l]");
    mvprintw(yPosition, xPosition + 26, "Pozostaly");
    mvprintw(yPosition + 1, xPosition + 26, "czas");

    if(drawLines){
        drawVerticalLine( yPosition, xPosition + 5, 60, ':');
        drawVerticalLine( yPosition, xPosition + 15, 60, ':');
        drawVerticalLine( yPosition, xPosition + 25, 60, ':');
    }
}


void NcursesView::drawDockAndParkingAreas(int headlineSpace, int docksXPosition, int parkingAreasXPosition) {
    attron(A_BOLD);
    drawSquares(docksXPosition, headlineSpace, false);             //docks
    drawSquares(parkingAreasXPosition, headlineSpace, true);       //truck parking areas
    attroff(A_BOLD);
}

void NcursesView::drawSquares(int startXPosition, int headlineSpace, bool textOnTheRight){
    for(int i = 0; i < numberOfDocks ; i++){
        move(i+1 + headlineSpace + 5*i, startXPosition - 3);
        printw("%d", i);
        drawSquare(i + headlineSpace +5*i, startXPosition);  // i + naglowek + (liczba lini kwadratu i przerwa) * i

        if(textOnTheRight){
            mvprintw(i + headlineSpace +5*i + 1, startXPosition + 7, "Statek: ");
            mvprintw(i + headlineSpace +5*i + 2, startXPosition + 7, "Cizarowka:");
        }
    }
}

void NcursesView::drawSquare(int yPosition, int xPosition){
    mvprintw(yPosition, xPosition, " ____");
    mvaddch(yPosition + 1, xPosition, '|');
    mvaddch(yPosition + 1, xPosition + 5, '|');
    mvaddch(yPosition + 2, xPosition, '|');
    mvaddch(yPosition + 2, xPosition + 5, '|');
    mvprintw(yPosition + 3, xPosition, "|____|");
}

void NcursesView::drawVerticalLine(int yPosition, int xPosition, int length, char symbol){
    for(int i = 0; i < length; i++){
        mvaddch(i + yPosition, xPosition, symbol);
    }
}

void NcursesView::drawHorizontalLine(int yPosition, int xPosition, int length, char symbol){
    for(int i = 0; i < length; i++){
        mvaddch(yPosition, i + xPosition, symbol);
    }
}


//-------------------------------simulation-------------------------------
bool NcursesView::exitView(){
    endwin();
    return true;
}

void NcursesView::test(std::string test) {
    std::lock_guard<std::mutex> lock(mutex);

    refresh();

}

void NcursesView::newShipAppears(int shipId, int capacityInLitres, int loadInLiters) {
    std::lock_guard<std::mutex> lock(mutex);
    int firstY = 21 + 5;
    int firstX = 95;

    move(firstY + lastShipPosInQueue, firstX);
    printw("%d", shipId);

    move(firstY + lastShipPosInQueue, firstX + 6);
    printw(" %d", capacityInLitres);

    move(firstY + lastShipPosInQueue, firstX + 16);
    printw(" %d", loadInLiters);

    lastShipPosInQueue = lastShipPosInQueue == 25 ? lastShipPosInQueue = 0 : ++lastShipPosInQueue;
    refresh();
}

void NcursesView::freeDock(int dockId){
    std::lock_guard<std::mutex> lock(mutex);
    int yChange = dockId + 5*dockId + 2;

    mvprintw(5 + yChange, 10 + 2, "  ");                       //in dock firstY = 0 + 5, firstX = 10

    mvprintw(5 + yChange - 1, 47, "  ");                      //ship info firstY = 0 + 5, firstX = 47
    mvprintw(5 + yChange - 1, 47 + 6, "  ");
    mvprintw(5 + yChange - 1, 47 + 16, "  ");

    mvprintw(5 + yChange, 17, "       ");

    move(2 + lastPanelInfoPos, 95);                //panel info firstY = 0 + 2, firstX = 95
    printw("Miejsce do cumowania %d zostalo zwolnione                    ", dockId);

    lastPanelInfoPos = lastPanelInfoPos == 15 ? lastPanelInfoPos = 0 : ++lastPanelInfoPos;
    refresh();
}

void NcursesView::occupyDock(int dockId, int shipId, int capacityInLitres, int loadInLiters) {
    std::lock_guard<std::mutex> lock(mutex);
    int yChange = dockId + 5*dockId + 2;

    move(5 + yChange, 10 + 2);                       //in dock firstY = 0 + 5, firstX = 10
    printw("%d", shipId);

    move(5 + yChange - 1, 47);                      //ship info firstY = 0 + 5, firstX = 47
    printw("%d", shipId);
    move(5 + yChange - 1, 47 + 6);
    printw("%d", capacityInLitres);
    move(5 + yChange - 1, 47 + 16);
    printw("%d", loadInLiters);

    move(2 + lastPanelInfoPos, 95);                //panel info firstY = 0 + 2, firstX = 95
    printw("Miejsce do cumowania %d zostalo zajete przez statek %d      ", dockId, shipId);

    lastPanelInfoPos = lastPanelInfoPos == 15 ? lastPanelInfoPos = 0 : ++lastPanelInfoPos;
    refresh();
}

void NcursesView::newTruckAppears(int truckId, int capacityInLitres, int loadInLiters) {
    std::lock_guard<std::mutex> lock(mutex);
    int firstY = 21 + 5;
    int firstX = 140;

    move(firstY + lastTruckPosInQueue, firstX);
    printw("%d", truckId);

    move(firstY + lastTruckPosInQueue, firstX + 6);
    printw(" %d", capacityInLitres);

    move(firstY + lastTruckPosInQueue, firstX + 16);
    printw(" %d", loadInLiters);

    lastTruckPosInQueue = lastTruckPosInQueue == 25 ? lastTruckPosInQueue = 0 : ++lastTruckPosInQueue;
    refresh();
}

void NcursesView::freeTruckParkingArea(int truckParkingAreaId) {
    std::lock_guard<std::mutex> lock(mutex);
    int yChange = truckParkingAreaId + 5*truckParkingAreaId + 2;

    mvprintw(5 + yChange, 25 + 2, "  ");                       //in dock firstY = 0 + 5, firstX = 25

    mvprintw(5 + yChange, 47, "  ");                          //ship info firstY = 0 + 5, firstX = 47
    mvprintw(5 + yChange, 47 + 6, "  ");
    mvprintw(5 + yChange, 47 + 16, "  ");

    mvprintw(5 + yChange, 17, "       ");

    move(2 + lastPanelInfoPos, 95);                //panel info firstY = 0 + 2, firstX = 95
    printw("Miejsce prakingowe %d zostalo zwolnione                   ", truckParkingAreaId);

    lastPanelInfoPos = lastPanelInfoPos == 15 ? lastPanelInfoPos = 0 : ++lastPanelInfoPos;
    refresh();
}

void NcursesView::occupyTruckParkingArea(int truckParkingAreaId, int truckId, int capacityInLitres, int loadInLiters) {
    std::lock_guard<std::mutex> lock(mutex);
    int yChange = truckParkingAreaId + 5*truckParkingAreaId + 2;

    move(5 + yChange, 25 + 2);                       //in dock firstY = 0 + 5, firstX = 25
    printw("%d", truckId);

    move(5 + yChange, 47);                          //ship info firstY = 0 + 5, firstX = 47
    printw("%d", truckId);
    move(5 + yChange, 47 + 6);
    printw("%d", capacityInLitres);
    move(5 + yChange, 47 + 16);
    printw("%d", loadInLiters);

    move(2 + lastPanelInfoPos, 95);                //panel info firstY = 0 + 2, firstX = 95
    printw("Miejsce prakingowe %d zostalo zajete przez ciezarowke %d      ", truckParkingAreaId, truckId);

    lastPanelInfoPos = lastPanelInfoPos == 15 ? lastPanelInfoPos = 0 : ++lastPanelInfoPos;
    refresh();
}

void NcursesView::reloadTruckToShip(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) {
    std::lock_guard<std::mutex> lock(mutex);
    int yChange = dockId + 5*dockId + 2;

    move(5 + yChange + 1, 17);
    printw("<--%d--", amount);

    move(5 + yChange, 47 + 16);
    printw("%d", truckLoadInLiters);
    move(5 + yChange - 1, 47 + 16);
    printw("%d", shipLoadInLiters);

    move(2 + lastPanelInfoPos, 95);                             //panel info firstY = 0 + 2, firstX = 95
    printw("Przeladowanie %d l ladunku z ciezarowki %d, do statku %d     ", amount, truckId, shipId);
    lastPanelInfoPos = lastPanelInfoPos == 15 ? lastPanelInfoPos = 0 : ++lastPanelInfoPos;

    refresh();
}

void NcursesView::reloadShipToTruck(int dockId, int shipId, int truckId, int amount, int truckLoadInLiters, int shipLoadInLiters) {
    std::lock_guard<std::mutex> lock(mutex);
    int yChange = dockId + 5*dockId + 2;

    move(5 + yChange + 1, 17);
    printw("--%d-->", amount);

    move(5 + yChange, 47 + 16);
    printw("%d", truckLoadInLiters);
    move(5 + yChange - 1, 47 + 16);
    printw("%d", shipLoadInLiters);


    move(2 + lastPanelInfoPos, 95);                           //panel info firstY = 0 + 2, firstX = 95
    printw("Przeladowanie %d l ladunku z statku %d, do ciezarowki %d     ", amount, shipId, truckId);
    lastPanelInfoPos = lastPanelInfoPos == 15 ? lastPanelInfoPos = 0 : ++lastPanelInfoPos;

    refresh();
}
