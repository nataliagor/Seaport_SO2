//
// Created by natalia on 18.05.23.
//

#include "Seaport.h"

Seaport::Seaport() {}

Seaport::~Seaport() {}

void Seaport::startWorking(){
    initializeView();
}

bool Seaport::initializeView(){
    view = new ConsoleView();
    return true;
}

bool Seaport::exitView(){
    return view->exitView();
}