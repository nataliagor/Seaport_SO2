//
// Created by natalia on 18.05.23.
//

#ifndef SEAPORT_SO2_IVIEW_H
#define SEAPORT_SO2_IVIEW_H


class IView {
public:
    virtual bool exitView() = 0;
    virtual void newShipAppears(int shipId) = 0;
    virtual void freeDock(int dockId) = 0;
    virtual void occupyDock(int dockId, int shipId) = 0;

};


#endif //SEAPORT_SO2_IVIEW_H
