//
// Created by natalia on 18.05.23.
//

#include "Seaport.h"

Seaport::Seaport(int numberOfDocks) : numberOfDocks(numberOfDocks), lastShipId(-1), lastTruckId(-1){
    for(int i = 0; i < numberOfDocks; i++){
        docks.push_back(new Dock(i));
        truckParkingAreas.push_back(new TruckParkingArea(i));
    }
}

Seaport::~Seaport() {}

void Seaport::startWorking(){
    initializeView();

    portAdministrator = new PortAdministrator();
    int doWhile2 = 100;
    adminThread = std::thread([&](){
        while(doWhile2 > 0) {
            doWhile2--;
            administratorLife();
        }
    });

    int doWhile = 10;
    while(doWhile > 0){
        doWhile--;
        shipsThreads.emplace_back([&](){                           //nowy watek dodawany do wektora shipsThreads
            shipLife();                                                     //kod wykonywany przez wątek
        });
    }

    for (auto& shipThread : shipsThreads) {
        if (shipThread.joinable()) {
            shipThread.join();
        }
    }
    adminThread.join();

}

bool Seaport::initializeView(){
    view = new ConsoleView();
    return true;
}

bool Seaport::exitView(){
    return view->exitView();
}

int Seaport::getRandomNumb(int min, int max){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

//------------------------------administrator-------------------------------
void Seaport::administratorLife(){
    giveLeavePermissions();
    giveDockPermissions();
    giveParkPermissions();
}

void Seaport::giveLeavePermissions(){
    setNumberOfLoadedShips(portAdministrator->givePermissionsToLeaveDock(getNumberOfLoadedShips()));
    //for trucks
}

void Seaport::giveDockPermissions(){
    std::lock_guard<std::mutex> lock(docksMutex);
    for (auto &dock: docks) {
        if (dock->checkIfFree()) {                                //tutaj inne warunki bedą -> narazie sprawdza tylko czy jest wolny
            portAdministrator->givePermissionToLoadedToDock(dock);
        }
    }
}

void Seaport::giveParkPermissions(){
    std::lock_guard<std::mutex> lock(truckParkingAreasMutex);
    for(auto& truckParking : truckParkingAreas){
        // TODO
    }
}

//-----------------------------------ship-----------------------------------
void Seaport::shipLife(){
    Ship *ship = newShipAppears();
    enterPort(ship);
    reloadShip(ship);
    leavePort(ship);
}

Ship* Seaport::newShipAppears(){
    std::lock_guard<std::mutex> lock(idMutex);
    lastShipId++;
    int capacityInLitres = getRandomNumb(0,6);
    Ship *newShip = new Ship(lastShipId, capacityInLitres, getRandomNumb(0,capacityInLitres), getRandomNumb(2, 48));

    view->newShipAppears(lastShipId);
    return newShip;
}

void Seaport::enterPort(Ship* ship){
    addShipToWaitingQueue(ship);
    while(ship->getDock() == nullptr){}
    //rozladowywanie / zaladowywanie
    //if loaded -> opusc port
    //if empty -> nie
}

bool Seaport::reloadShip(Ship* ship){

}

void Seaport::leavePort(Ship* ship){
    portAdministrator->addToShipsToLeaveQueue(ship);
    while(ship->getDock() != nullptr){}
    ship->leaveSeaport();
    delete ship;
}

void Seaport::addShipToWaitingQueue(Ship *ship){
    (ship->isEmpty()) ? portAdministrator->addToEmptyShipsToDockQueue(ship) : portAdministrator->addToLoadedShipsToDockQueue(ship);
}


//-----------------------------------truck-----------------------------------
void Seaport::newTruckAppears(){
    std::lock_guard<std::mutex> lock(idMutex);
    lastTruckId++;
}


//----------------------------getters and setters----------------------------
int Seaport::getNumberOfEmptyTrucks(){
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    return numberOfEmptyTrucks;
}

void Seaport::setNumberOfEmptyTrucks(int numberOfEmptyTrucks) {
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    Seaport::numberOfEmptyTrucks = numberOfEmptyTrucks;
}

int Seaport::getNumberOfEmptyShips(){
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    return numberOfEmptyShips;
}

void Seaport::setNumberOfEmptyShips(int numberOfEmptyShips) {
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    Seaport::numberOfEmptyShips = numberOfEmptyShips;
}

int Seaport::getNumberOfLoadedTrucks(){
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    return numberOfLoadedTrucks;
}

void Seaport::setNumberOfLoadedTrucks(int numberOfLoadedTrucks) {
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    Seaport::numberOfLoadedTrucks = numberOfLoadedTrucks;
}

int Seaport::getNumberOfLoadedShips(){
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    return numberOfLoadedShips;
}

void Seaport::setNumberOfLoadedShips(int numberOfLoadedShips) {
    std::lock_guard<std::mutex> lock(countVehiclesMutex);
    Seaport::numberOfLoadedShips = numberOfLoadedShips;
}


