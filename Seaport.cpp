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

    portAdministrator = new PortAdministrator(*view);                      //administrator portu
    adminThread = std::thread([&](){
        while(true) {
            administratorLife();
        }
    });

    timeActualizeThread = std::thread([&](){                        //aktualizacja czasu
        while(true) {
            actualizeTimeInPort();
        }
    });

    shipCreator = std::thread([&](){
        while(true){                                                              //statki
            shipsThreads.emplace_back([&](){                           //nowy watek dodawany do wektora shipsThreads
                shipLife();                                                     //kod wykonywany przez wątek
            });
            sleep(getRandomNumb(0,7));
        }
        for (auto& shipThread : shipsThreads) {
            if (shipThread.joinable()) {
                shipThread.join();
            }
        }
    });

    truckCreator = std::thread([&]() {
        while (true) {                                                        //ciezarowki
            trucksThreads.emplace_back([&]() {
                trucksLife();
            });
            sleep(getRandomNumb(0,5));
        }
        for (auto& truckThread : trucksThreads) {
            if (truckThread.joinable()) {
                truckThread.join();
            }
        }
    });

    adminThread.join();                                                     //laczenie wszystkich watkow
    shipCreator.join();
    truckCreator.join();
    timeActualizeThread.join();
    exitView();
}


bool Seaport::initializeView(){
    view = new NcursesView(numberOfDocks);
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
    setNumberOfLoadedShips(portAdministrator->giveLoadedPermissionsToLeaveDock(getNumberOfLoadedShips()));
    setNumberOfLoadedTrucks(portAdministrator->giveLoadedPermissionsToLeaveParking(getNumberOfLoadedTrucks()));
    setNumberOfEmptyShips(portAdministrator->giveEmptyPermissionsToLeaveDock(getNumberOfEmptyShips()));
    setNumberOfEmptyTrucks(portAdministrator->giveEmptyPermissionsToLeaveParking(getNumberOfEmptyTrucks()));
}

void Seaport::giveDockPermissions(){
    for (auto &dock: getDocks()) {
        if (dock->isAvailable()) {
            dockShip(dock);
        }
    }
}

bool Seaport::checkIfEmptyShipIsNeeded(Dock* dock){
    TruckParkingArea* truckParkingArea = getTruckParkingAreaById(dock->getId());
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
    for(auto& truckParking : getTruckParkingAreas()){
        if(truckParking->isAvailable()){
            parkTruck(truckParking);
        }
    }
}

bool Seaport::checkIfEmptyTruckIsNeeded(TruckParkingArea* truckParkingArea){
    Dock* dock = getDockById(truckParkingArea->getId());
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
    sleep(1);

    enterPort(ship);
    sleep(5);

    reloadShip(ship);          //operacje wykonuje tylko nowo przybyly statek/cezarowka
    sleep(3);

    while(!ship->isStatusChanged()){}
    sleep(2);
    leavePort(ship);
    sleep(1);
}

Ship* Seaport::newShipAppears(){
    int shipId = getCurrentShipId();

    int capacityInLitres = getRandomNumb(1,12);
    int loadInLiters = getRandomNumb(0,1) == 0 ? 0 : getRandomNumb(1,capacityInLitres);
    int maxTimeInPort = getRandomNumb(12, 36);
    Ship *newShip = new Ship(shipId, capacityInLitres,loadInLiters, maxTimeInPort);

    addVehicleToVehiclesVector(newShip);
    view->newShipAppears(shipId, capacityInLitres, loadInLiters, maxTimeInPort);
    return newShip;
}

void Seaport::enterPort(Ship* ship){
    addShipToWaitingQueue(ship);
    while(ship->getDock() == nullptr){}
}

bool Seaport::reloadShip(Ship* ship){
    std::lock_guard<std::mutex> lock(reloadingMutex);
    Truck *truck = getTruckParkingAreaById(ship->getDock()->getId())->getTruck();
    if(truck == nullptr || ship->isStatusChanged() || truck->isStatusChanged()) return false; //|| ship->isStatusChanged() || truck->isStatusChanged()

    if(ship->isEmpty() || ship->isBeingLoaded()){                                       // zaladowywanie
        reloadTruckToShip(ship, truck);
    }else{                                                                              // rozladowywanie
        reloadShipToTruck(ship, truck);
    }
    return true;
}

void Seaport::leavePort(Ship* ship){
    (ship->isLoaded()) ? portAdministrator->addToLoadedShipsToLeaveQueue(ship) : portAdministrator->addToEmptyShipsToLeaveQueue(ship);

    while(ship->getDock() != nullptr){}
    ship->leaveSeaport(); //nie trzba bo wszytsko powinno byc juz zwolnione u daministratoa, ale na wszelki wypadek
    deleteVehicleFromVehiclesVector(ship);
    delete ship;
}

void Seaport::addShipToWaitingQueue(Ship *ship){
    (ship->isEmpty()) ? portAdministrator->addToEmptyShipsToDockQueue(ship) : portAdministrator->addToLoadedShipsToDockQueue(ship);
}

bool Seaport::reloadTruckToShip(Ship *ship, Truck* truck){
    int shipSpaceLeft = ship->getCapacityInLitres() - ship->getLoadInLiters();
    int truckLoadInLitters = truck->getLoadInLiters();
    int amount = truckLoadInLitters >= shipSpaceLeft ? shipSpaceLeft : truckLoadInLitters;

    ship->load(amount);
    truck->unload(amount);

    if(ship->isFull()){
        setNumberOfEmptyShips(getNumberOfEmptyShips() - 1);
        setNumberOfLoadedShips(getNumberOfLoadedShips() + 1);
    }

    view->reloadTruckToShip(ship->getDock()->getId(), ship->getId(), truck->getId(), amount, truck->getLoadInLiters(), ship->getLoadInLiters());
    return true;
}

bool Seaport::reloadShipToTruck(Ship *ship, Truck* truck){
    int truckSpaceLeft = truck->getCapacityInLitres() - truck->getLoadInLiters();
    int shipLoadInLitters = ship->getLoadInLiters();
    int amount =  shipLoadInLitters >= truckSpaceLeft ? truckSpaceLeft : shipLoadInLitters;

    truck->load(amount);
    ship->unload(amount);

    if(truck->isFull()){
        setNumberOfEmptyShips(getNumberOfEmptyTrucks() - 1);
        setNumberOfLoadedTrucks(getNumberOfLoadedTrucks() + 1);
    }

    view->reloadShipToTruck(ship->getDock()->getId(), ship->getId(), truck->getId(), amount, truck->getLoadInLiters(), ship->getLoadInLiters());
    return true;
}

//-----------------------------------truck-----------------------------------
void Seaport::trucksLife(){
    Truck *truck = newTruckAppears();
    sleep(1);
    enterPort(truck);
    sleep(5);
    reloadTruck(truck);
    sleep(3);

    while(!truck->isStatusChanged()){}
    sleep(2);
    leavePort(truck);
    sleep(1);
}

Truck* Seaport::newTruckAppears(){
    int truckId = getCurrentTruckId();
    int capacityInLitres = getRandomNumb(1,6);
    int loadInLiters = getRandomNumb(0,1) == 0 ? 0 : getRandomNumb(1,capacityInLitres);
    int maxTimeInPort = getRandomNumb(6, 48);
    Truck *newTruck = new Truck(truckId, capacityInLitres, loadInLiters, maxTimeInPort);

    addVehicleToVehiclesVector(newTruck);
    view->newTruckAppears(truckId, capacityInLitres, loadInLiters, maxTimeInPort);
    return newTruck;
}

void Seaport::enterPort(Truck* truck){
    addTruckToWaitingQueue(truck);
    while(truck->getTruckParkingArea() == nullptr){}
}

void Seaport::addTruckToWaitingQueue(Truck* truck){
    (truck->isEmpty()) ? portAdministrator->addToEmptyTrucksToParkQueue(truck) : portAdministrator->addToLoadedTrucksToParkQueue(truck);
}

bool Seaport::reloadTruck(Truck* truck){
    std::lock_guard<std::mutex> lock(reloadingMutex);
    Ship *ship = getDockById(truck->getTruckParkingArea()->getId())->getShip();
    if(ship == nullptr || ship->isStatusChanged() || truck->isStatusChanged()) return false; //|| ship->isStatusChanged() || truck->isStatusChanged()

    if(truck->isEmpty() || truck->isBeingLoaded()){                                       // zaladowywanie
        reloadShipToTruck(ship, truck);
    }else{                                                                                //rozladowywanie
        reloadTruckToShip(ship, truck);
    }
    return true;
}

void Seaport::leavePort(Truck* truck){
    (truck->isLoaded()) ? portAdministrator->addToLoadedTrucksToLeaveQueue(truck) : portAdministrator->addToEmptyTrucksToLeaveQueue(truck);

    while(truck->getTruckParkingArea() != nullptr){}
    truck->leaveSeaport(); //nie trzba bo wszytsko powinno byc juz zwolnione u daministratoa, ale na wszelki wypadek
    deleteVehicleFromVehiclesVector(truck);
    delete truck;
}


//-----------------------vehicles vector and time in port-----------------------

void Seaport::addVehicleToVehiclesVector(Vehicle* vehicle){
    std::lock_guard<std::mutex> lock(vehiclesMutex);
    vehicles.push_back(vehicle);
}

void Seaport::deleteVehicleFromVehiclesVector(Vehicle* vehicle){
    std::lock_guard<std::mutex> lock(vehiclesMutex);
    vehicles.erase(std::remove(vehicles.begin(), vehicles.end(), vehicle), vehicles.end());
}

void Seaport::actualizeTimeInPort(){
    sleep(3);
    std::lock_guard<std::mutex> lock(vehiclesMutex);
    for (Vehicle* vehicle : vehicles) {
        vehicle->setTimeInPort(vehicle->getTimeInPort() + 1);
    }

    view->showShipsQueue(0, 0, 0, true);
    view->showTruckQueue(0, 0, 0, true);
    std::vector<Vehicle*> copyVector  = vehicles;
    for (Vehicle* vehicle : copyVector) {
        if(typeid(*vehicle) == typeid(Ship))
            view->showShipsQueue(vehicle->getId(), vehicle->getMaxTimeInPort(), vehicle->getTimeInPort(), false);
        if(typeid(*vehicle) == typeid(Truck))
            view->showTruckQueue(vehicle->getId(), vehicle->getMaxTimeInPort(), vehicle->getTimeInPort(), false);
    }
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

int Seaport::getCurrentShipId(){
    std::lock_guard<std::mutex> lock(lastShipIdMutex);
    Seaport::lastShipId = lastShipId == 999 ? lastShipId = 0 : ++lastShipId;
    return lastShipId;
}

int Seaport::getCurrentTruckId(){
    std::lock_guard<std::mutex> lock(lastTruckIdMutex);
    Seaport::lastTruckId =  lastTruckId == 999 ? lastTruckId = 0 :++lastTruckId;
    return lastTruckId;
}

std::vector<Dock *> &Seaport::getDocks(){
    std::lock_guard<std::mutex> lock(docksMutex);
    return docks;
}

std::vector<TruckParkingArea *> &Seaport::getTruckParkingAreas(){
    std::lock_guard<std::mutex> lock(parkingAreasMutex);
    return truckParkingAreas;
}

Dock* Seaport::getDockById(int id){
    std::lock_guard<std::mutex> lock(docksMutex);
    return docks[id];
}

TruckParkingArea* Seaport::getTruckParkingAreaById(int id){
    std::lock_guard<std::mutex> lock(parkingAreasMutex);
    return truckParkingAreas[id];
}






