//
// Created by natalia on 18.05.23.
//

#include "NcursesView.h"
#include <ncurses.h>

NcursesView::NcursesView() {
    initscr();
    printw("Hi");
    refresh();
    getch();
}

NcursesView::~NcursesView() {

}

bool NcursesView::exitView(){
    endwin();
    return true;
}
