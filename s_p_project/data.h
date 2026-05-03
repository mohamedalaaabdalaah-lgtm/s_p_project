// this file contains the structures of data that we will use in our project and the global variables that we will use to store the data of planes, flights and tickets.
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <string>
#include "stdafx.h"
using namespace std;


struct model_of_plane //structure of model of plane
{
    string plane_model;
    int number_of_row;//هتتغير حسب نوع الطياره
    int number_of_col;//هتتغير حسب نوع الطياره
    string seat_letters;

};

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
    int plane_code;
    int number_of_rows;//هتتغير حسب نوع الطياره
    int number_of_col;//هتتغير حسب نوع الطياره
    string seat_letters;//هتتغير حسب نوع الطياره 


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
    bool is_empty = true;
    int rows_number;
    int columns_number;
    int flight_code;
    int for_planecode;//ده عشان كل رحله تبقي يشاور علي طيارتها 
    char seats[100][10];// دي رقم كبير ولما اجي اطبع هبقي اطبع علي حسب رقم الصفوف والعمده 
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


struct ticket
{
    string passenger_name;
    string passport_id;
    int flight_number;//الي فيها الكرسي بتاع التذكرة دي 
    string departure_city;
    string arrival_city;
    mydate date;
    mytime time;
    int seat_row;
    char seat_letter;
};


//global variables
extern vector <plane> plane_list;//vectors of planes to able to add plans by admin(dynamicaly)
extern vector <flight> flight_list;//vectors of flights to able to add flights by admin(dynamicaly)
extern vector <ticket> tickets_list;//vectors of tickets to able to add tickets by user(dynamicaly)

extern admin admins[10];
extern model_of_plane models[5];//ثابتين ولا بيزيدو ولا بيقيلوا وهنكتبهم في الكود 

extern int choice;
extern string keyword;
extern string details_choice;
extern int found ;
extern int days ;
extern string months ;

extern user current_user;
extern flight currentFlight;


extern int  user_row;
extern char user_colum;
extern int indexRow, indexColum;
extern int current_flight_index;

#endif