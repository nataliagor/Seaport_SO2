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
