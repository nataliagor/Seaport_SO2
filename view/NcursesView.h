//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_NCURSESVIEW_H
#define SEAPORT_SO2_NCURSESVIEW_H

#include "IView.h"

class NcursesView : public IView{
public:
    NcursesView();
    virtual ~NcursesView();

    virtual bool exitView();
};


#endif //SEAPORT_SO2_NCURSESVIEW_H
