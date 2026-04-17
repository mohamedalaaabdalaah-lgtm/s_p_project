//list of includes in main.cpp
#include "stdafx.h"
#include "s_p_project.h"
#include <QtWidgets/QApplication>
#include <string>
#include <vector>
#include <iostream>;
using namespace std;


struct mydate //structure of date
{
    int day, month;
};

struct mytime //structure of time 
{
    int hours, minutes;
};

struct plane //structure of plane
{
    string plane_model;
    int number_of_Rows, plane_code;
    char seat_letters;
};

struct flight //structure of flight
{
    int flight_number;
    string departure_city, arrival_city, departure_airport, arrival_airport;
    mydate departure_date, arrival_date;
    mytime departure_time, arrival_time;
    int Flight_Code;
    vector<vector<string>> seats_status; //2d vector status of seats in the plane ("name of passenger" for busy, "Available"  for available)
} ; 

struct admin //structure of flight
{
    string username, password;
}admins[10];//الرقم ده من عندي كدا


struct user //structure of user
{
    string username;
    string passport_id;
};


struct Ticket//structure of ticket ( passport_id<<32b43  ,  flight<<583  ,   planecode<<4321   ,   seat<<4c  )
{

    string passenger_name, passport_id;
    int flight_number, plane_code;
    int seat_row;
    char seat_letter;
};




//global variables
vector <plane> planes_list(10);//vectors of planes to able to add plans by admin(dynamicaly)
vector <flight> flight_list(20);//vectors of flights to able to add flights by admin(dynamicaly)
vector <Ticket> tickets_list;//vectors of tickets to able to add tickets by user(dynamicaly)



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    s_p_project window;
    window.show();






    return app.exec();
}
