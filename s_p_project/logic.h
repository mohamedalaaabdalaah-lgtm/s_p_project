#ifndef LOGIC_H
#define LOGIC_H
#include "data.h"
#include "stdafx.h"

void start();



//backend functions(admin)
void add_plane();
void update_plane();
void add_flight();
void update_flight();
bool login();
void admin_path();
void search_flight();
void search_plane();


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//


//backend functions(user)
void Display_Flight(flight details);
void user_login();
int Search_Ways_Menu();
string Checking_City_Letters(string city);//بتشيك ان الحروف كبيره ولا صغيره 
void Checking_Date();
void Keyword_Search(int choice);
void search_Flights(int choice);
void Display_Seats(flight current_flight);
void book_Seats();
void see_ticket();
void user_path();


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

//gui functions
void add_plane_gui(string model, int code);
bool add_flight_gui(int planecode, int flightcode, string depCity, string arrCity, string depAirport, string arrAirport,
    int depDay, string depMonth, int arrDay, string arrMonth, int depHour, int depMinute, int arrHour, int arrMinute);

//user 
void user_login_gui(string name, string passport);



#endif
