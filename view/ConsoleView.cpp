//
// Created by natalia on 18.05.23.
//

#include "ConsoleView.h"

ConsoleView::ConsoleView() {
    std::cout << "Witaj w porcie!" << std::endl;
}

ConsoleView::~ConsoleView() {}

bool ConsoleView::exitView(){
    std::cout << "Zegnaj!" << std::endl;
    return true;
}

void ConsoleView::newShipAppears(int shipId){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Pojawil sie nowy statek o id  " << shipId << std::endl;
}

void ConsoleView::freeDock(int dockId){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Miejsce do cumowania " << dockId << " zostalo zwolnione" << std::endl;
}

void ConsoleView::occupyDock(int dockId, int shipId){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Miejsce do cumowania " << dockId << " zostalo zajete przez statek " <<  shipId << std::endl;
}

