#ifndef LOGIC_H
#define LOGIC_H
#include "data.h"
#include "stdafx.h"

void add_plane();
void update_plane();
void add_flight();
void update_flight();
bool login();
void admin_path();
void start();
void search_flight();
void search_plane();
void add_plane_gui(string model, int code);//the new function
bool add_flight_gui(int planecode, int flightcode, string depCity, string arrCity, string depAirport, string arrAirport,
    int depDay, int depMonth, int arrDay, int arrMonth, int depHour, int depMinute, int arrHour, int arrMinute);

#endif
