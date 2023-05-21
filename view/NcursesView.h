//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_NCURSESVIEW_H
#define SEAPORT_SO2_NCURSESVIEW_H

#include <mutex>
#include "IView.h"

class NcursesView : public IView{
    std::mutex mutex;
public:
    NcursesView();
    virtual ~NcursesView();

    bool exitView() override;
};


#endif //SEAPORT_SO2_NCURSESVIEW_H
