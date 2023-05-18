//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_SEAPORT_H
#define SEAPORT_SO2_SEAPORT_H

#include "view/IView.h"
#include "view/ConsoleView.h"
#include "view/NcursesView.h"


class Seaport {
    IView* view;

public:
    Seaport();
    virtual ~Seaport();
    void startWorking();

private:
    bool initializeView();
    bool exitView();

};


#endif //SEAPORT_SO2_SEAPORT_H
