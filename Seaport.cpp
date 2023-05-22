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

    portAdministrator = new PortAdministrator(*view);
    int doWhile2 = 3000;
    adminThread = std::thread([&](){
        while(doWhile2 > 0) {
            doWhile2--;
            administratorLife();
        }
    });

    int doWhile = 30;
    while(doWhile > 0){
        doWhile--;
        shipsThreads.emplace_back([&](){                           //nowy watek dodawany do wektora shipsThreads
            shipLife();                                                     //kod wykonywany przez wątek
        });
    }

    int doWhile3 = 30;
    while(doWhile3 > 0){
        doWhile3--;
        trucksThreads.emplace_back([&](){
            trucksLife();
        });
    }

    adminThread.join();
    for (auto& shipThread : shipsThreads) {
        if (shipThread.joinable()) {
            shipThread.join();
        }
    }
    for (auto& truckThread : trucksThreads) {
        if (truckThread.joinable()) {
            truckThread.join();
        }
    }
    exitView();
}

bool Seaport::initializeView(){
    view = new ConsoleView();
    return true;
}

bool Seaport::exitView(){
    return view->exitView();
}

int Seaport::getRandomNumb(int min, int max){
    std::lock_guard<std::mutex> lock(randMutex);
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
    setNumberOfLoadedTrucks(portAdministrator->givePermissionsToLeaveParking(getNumberOfLoadedTrucks()));
}

void Seaport::giveDockPermissions(){
    std::lock_guard<std::mutex> lock(docksAndParkingAreasMutex);
    for (auto &dock: docks) {
        if (dock->isAvailable()) {
            dockShip(dock);
        }
    }
}

bool Seaport::checkIfEmptyShipIsNeeded(Dock* dock){
    TruckParkingArea* truckParkingArea = truckParkingAreas[dock->getId()];
    if(!truckParkingArea->isAvailable() && (truckParkingArea->getTruck()->isLoaded() || truckParkingArea->getTruck()->isBeingUnloaded())) {
        return true;
    }
    return false;
}

void Seaport::dockShip(Dock* dock){
    if(checkIfEmptyShipIsNeeded(dock)){
        if(portAdministrator->givePermissionToEmptyToDock(dock)){
            int emptyShips = getNumberOfEmptyShips() + 1;
            setNumberOfEmptyShips(emptyShips);}
    }else{
        if(portAdministrator->givePermissionToLoadedToDock(dock)){
            int loadedShips = getNumberOfLoadedShips() + 1;
            setNumberOfLoadedShips(loadedShips);}
    }
}

void Seaport::giveParkPermissions(){
    std::lock_guard<std::mutex> lock(docksAndParkingAreasMutex);
    for(auto& truckParking : truckParkingAreas){
        if(truckParking->isAvailable()){
            parkTruck(truckParking);
        }
    }
}

bool Seaport::checkIfEmptyTruckIsNeeded(TruckParkingArea* truckParkingArea){
    Dock* dock = docks[truckParkingArea->getId()];
    if(!dock->isAvailable() && (dock->getShip()->isLoaded() || dock->getShip()->isBeingUnloaded())) {
        return true;
    }
    return false;
}

void Seaport::parkTruck(TruckParkingArea* truckParkingArea){
    if(checkIfEmptyTruckIsNeeded(truckParkingArea)){
        if(portAdministrator->givePermissionToEmptyToPark(truckParkingArea)){
            int emptyTrucks = getNumberOfEmptyTrucks() + 1;
            setNumberOfEmptyTrucks(emptyTrucks);}
    }else{
        if(portAdministrator->givePermissionToLoadedToPark(truckParkingArea)){
            int loadedTrucks = getNumberOfLoadedTrucks() + 1;
            setNumberOfLoadedTrucks(loadedTrucks);}
    }
}

//-----------------------------------ship-----------------------------------
void Seaport::shipLife(){
    Ship *ship = newShipAppears();
    enterPort(ship);
    unloadShip(ship);
    leavePort(ship);
    // jeśli nie jest loaded to opusc port w przeciwnym razie nie //TODO
}

Ship* Seaport::newShipAppears(){
    std::lock_guard<std::mutex> lock(shipIdMutex);
    lastShipId++;
    int capacityInLitres = getRandomNumb(0,6);
    Ship *newShip = new Ship(lastShipId, capacityInLitres, getRandomNumb(0,capacityInLitres), getRandomNumb(2, 48));

    view->newShipAppears(lastShipId);
    return newShip;
}

void Seaport::enterPort(Ship* ship){
    addShipToWaitingQueue(ship);
    while(ship->getDock() == nullptr){}
}

bool Seaport::unloadShip(Ship* ship){
    //rozladowywanie / zaladowywanie //TODO
    //if loaded -> opusc port
    //if empty -> nie
    return true;
}

void Seaport::leavePort(Ship* ship){
    portAdministrator->addToShipsToLeaveQueue(ship);
    while(ship->getDock() != nullptr){}
    //ship->leaveSeaport();
    delete ship;
}

void Seaport::addShipToWaitingQueue(Ship *ship){
    (ship->isEmpty()) ? portAdministrator->addToEmptyShipsToDockQueue(ship) : portAdministrator->addToLoadedShipsToDockQueue(ship);
}


//-----------------------------------truck-----------------------------------
void Seaport::trucksLife(){
    Truck *truck = newTruckAppears();
    enterPort(truck);
    unloadTruck(truck);
    leavePort(truck);
}

Truck* Seaport::newTruckAppears(){
    std::lock_guard<std::mutex> lock(truckIdMutex);
    lastTruckId++;
    int capacityInLitres = getRandomNumb(0,6);
    Truck *newTruck = new Truck(lastTruckId, capacityInLitres, getRandomNumb(0,capacityInLitres), getRandomNumb(2, 48));

    view->newTruckAppears(lastTruckId);
    return newTruck;
}

void Seaport::enterPort(Truck* truck){
    addTruckToWaitingQueue(truck);
    while(truck->getTruckParkingArea() == nullptr){}
}

void Seaport::addTruckToWaitingQueue(Truck* truck){
    (truck->isEmpty()) ? portAdministrator->addToEmptyTrucksToParkQueue(truck) : portAdministrator->addToLoadedTrucksToParkQueue(truck);
}

void Seaport::leavePort(Truck* truck){
    portAdministrator->addToTrucksToLeaveQueue(truck);
    while(truck->getTruckParkingArea() != nullptr){}
    //truck->leaveSeaport();
    delete truck;
}

bool Seaport::unloadTruck(Truck* truck){
    //rozladowywanie / zaladowywanie //TODO
    //if loaded -> opusc port
    //if empty -> nie
    return true;
}


//----------------------------getters and setters----------------------------
int Seaport::getNumberOfEmptyTrucks(){
    std::lock_guard<std::mutex> lock(emptyTrucksMutex);
    return numberOfEmptyTrucks;
}

void Seaport::setNumberOfEmptyTrucks(int numberOfEmptyTrucks) {
    std::lock_guard<std::mutex> lock(emptyTrucksMutex);
    Seaport::numberOfEmptyTrucks = numberOfEmptyTrucks;
}

int Seaport::getNumberOfEmptyShips(){
    std::lock_guard<std::mutex> lock(emptyShipsMutex);
    return numberOfEmptyShips;
}

void Seaport::setNumberOfEmptyShips(int numberOfEmptyShips) {
    std::lock_guard<std::mutex> lock(emptyShipsMutex);
    Seaport::numberOfEmptyShips = numberOfEmptyShips;
}

int Seaport::getNumberOfLoadedTrucks(){
    std::lock_guard<std::mutex> lock(loadedTrucksMutex);
    return numberOfLoadedTrucks;
}

void Seaport::setNumberOfLoadedTrucks(int numberOfLoadedTrucks) {
    std::lock_guard<std::mutex> lock(loadedTrucksMutex);
    Seaport::numberOfLoadedTrucks = numberOfLoadedTrucks;
}

int Seaport::getNumberOfLoadedShips(){
    std::lock_guard<std::mutex> lock(loadedShipsMutex);
    return numberOfLoadedShips;
}

void Seaport::setNumberOfLoadedShips(int numberOfLoadedShips) {
    std::lock_guard<std::mutex> lock(loadedShipsMutex);
    Seaport::numberOfLoadedShips = numberOfLoadedShips;
}


