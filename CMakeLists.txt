cmake_minimum_required(VERSION 3.24)
project(Seaport_SO2)

set(CMAKE_CXX_STANDARD 23)

add_executable(Seaport_SO2 main.cpp view/ConsoleView.cpp view/ConsoleView.h view/NcursesView.cpp view/NcursesView.h view/IView.h)
