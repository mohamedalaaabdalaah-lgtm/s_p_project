#include "stdafx.h"
#include "data.h"

//global variables
vector <plane> plane_list(10);//vectors of planes to able to add plans by admin(dynamicaly)
vector <flight> flight_list(20);//vectors of flights to able to add flights by admin(dynamicaly)
vector <ticket> tickets_list;//vectors of tickets to able to add tickets by user(dynamicaly)




int choice;
string keyword;
string details_choice;
int found = 0;
int days = 0;
string months = "";

user current_user;
flight currentFlight;


int  user_row;
char user_colum;
int indexRow, indexColum;
int current_flight_index;

admin admins[10];//الرقم ده من عندي كدا
model_of_plane models[5];//ده رقم انواع الطائرات الي عندنا
