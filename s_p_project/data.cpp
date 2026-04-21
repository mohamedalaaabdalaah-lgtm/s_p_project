#include "stdafx.h"
#include "data.h"

//global variables
vector <plane> plane_list(10);//vectors of planes to able to add plans by admin(dynamicaly)
vector <flight> flight_list(20);//vectors of flights to able to add flights by admin(dynamicaly)
ticket* tickets_list = NULL;//نبدأ بيها عشان هو مش بيشير الي حاجه 
int tickets_count = 0;
admin admins[10];//الرقم ده من عندي كدا
model_of_plane models[10];//ده رقم انواع الطائرات الي عندنا
