//
// Created by natalia on 18.05.23.
//

#include "Seaport.h"

Seaport::Seaport(int numberOfDocks) : numberOfDocks(numberOfDocks), lastShipId(0), lastTruckId(0){
    for(int i = 0; i < numberOfDocks; i++){
        docks.push_back(new Dock(i));
        truckParkingAreas.push_back(new TruckParkingArea(i));
    }
}

Seaport::~Seaport() {}

void Seaport::startWorking(){
    initializeView();
    int doWhile = 10;
    newShipAppears();

    while(doWhile > 0){
        doWhile --;
        //std::this_thread::sleep_for(std::chrono::seconds(2));            //random sleep -> co ile pojawiają się now statki
        shipsThreads.emplace_back([&]() {                         //nowy wątek
            Ship* ship = newShipAppears();                                 //nowy statek + dodanie go do kolejki priorytetowej
                                                                            //zapytanie administratora o pozwolenie wpłynięcia
                                                                                //-> pozytywna opinia
                                                                                    // -> cumowanie statku (administrator
                                                                                            //  - patrzy czy są wolne doki
                                                                                            //  - sprawdza czy jest pusty czy zajęty
                                                                                            //  - sprawdza czy pustych statków - zajętcyh ciezarówek i na odwrót
                                                                                            // - sprawdza czy jest 1 w kolejce z porządanymi wymaganiami
                                                                                            //  - jeśli tak usówa z koleji
                                                                                            //  - i blokuje wolny dok)
                                                                                    // ->
                                                                                // -> negatywna opinia -> nic, czeka dalej
            delete ship;                                                        // usunięcie statku
        });
    }

    for (auto& shipThread : shipsThreads) {
        if (shipThread.joinable()) {
            shipThread.join();
        }
    }

}

bool Seaport::initializeView(){
    view = new ConsoleView();
    return true;
}

bool Seaport::exitView(){
    return view->exitView();
}

Ship* Seaport::newShipAppears(){
    std::lock_guard<std::mutex> lock(mutex);
    lastShipId++;
    int capacityInLitres = 3;       // tutaj dać random <1,6>
    int loadInLiters = 0;           // tutaj dać random <0, capacityInLiters>
    int maxTimeInPort = 3;          // tutaj random < , > w dniach?, w godzianch?
    Ship *newShip = new Ship(lastShipId, capacityInLitres, loadInLiters, maxTimeInPort);
    shipsQueue.push(newShip);
    view->newShipAppears(lastShipId);
    return newShip;
}

void Seaport::newTruckAppears(){
    lastTruckId++;
    int capacityInLitres = 3;       // tutaj dać random <1,6>
    int loadInLiters = 3;           // tutaj dać random <0, capacityInLiters>
    int maxTimeInPort = 3;          // tutaj random < , > w dniach?, w godzianch?
    trucksQueue.push(new Truck(lastTruckId, capacityInLitres, loadInLiters, maxTimeInPort));
}