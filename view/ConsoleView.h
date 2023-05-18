//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_CONSOLEVIEW_H
#define SEAPORT_SO2_CONSOLEVIEW_H

#include "IView.h"
#include <iostream>

class ConsoleView : public IView{
public:
    ConsoleView();
    virtual ~ConsoleView();

    virtual bool exitView();

private:
};


#endif //SEAPORT_SO2_CONSOLEVIEW_H
