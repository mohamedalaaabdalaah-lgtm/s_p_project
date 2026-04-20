// this file contains the structures of data that we will use in our project and the global variables that we will use to store the data of planes, flights and tickets.
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <string>
#include "stdafx.h"
using namespace std;


struct mydate //structure of date
{
    int day;
    string month;
};

struct mytime //structure of time 
{
    int hours;
    int minutes;
};

struct plane //structure of plane
{
    string plane_model;
    int number_of_rows;
    int plane_code;
    char** seats_p; // 2d dynamic array by pointers
};

struct flight //structure of flight
{
    string departure_city;
    string arrival_city;
    string departure_airport;
    string arrival_airport;
    mydate departure_date;
    mydate arrival_date;
    mytime departure_time;
    mytime arrival_time;
    int flight_code;
    char** seats_f; // 2d dynamic array by pointers
};

struct admin //structure of admin
{
    string username;
    string password;
};


struct user //structure of user
{
    string username;
    string passport_id;
};


struct ticket//structure of ticket ( passport_id<<32b43  ,  flight<<583  ,   planecode<<4321   ,   seat<<4c  )
{

    string passenger_name;
    string passport_id;
    int flight_number;
    int plane_code;
    int seat_row;
    char seat_letter;
};



//global variables
extern vector <plane> plane_list;//vectors of planes to able to add plans by admin(dynamicaly)
extern vector <flight> flight_list;//vectors of flights to able to add flights by admin(dynamicaly)


extern int tickets_count;//to count of tickets that we have in our system to be able to add new tickets by user(dynamicaly)
extern ticket* tickets_list;//dynamic array of tickets to able to add tickets by user(dynamicaly)

 

extern admin admins[10];//الرقم ده من عندي كدا


#endif