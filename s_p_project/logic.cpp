#include "stdafx.h"
#include "logic.h"
#include "data.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


void add_plane()
{
    plane* ptr = new plane();
    bool model_found = false;
    cout << "\n Enter the plane model : \n ";
    cin >> (*ptr).plane_model;

    for (int i = 0; i < 5; i++)//اللووب دي عشان تربط وتحط الصفوف والاعمده بتاعت نوع الطياره الي الادمن دخلها 
    {
        if (models[i].plane_model == (*ptr).plane_model)
        {
            model_found = true;
            (*ptr).number_of_rows = models[i].number_of_row;
            (*ptr).number_of_col = models[i].number_of_col;
            (*ptr).seat_letters = models[i].seat_letters;

            cout << "\n Enter the plane code : \n ";
            cin >> (*ptr).plane_code;

        }
    }
    if (model_found == false)
    {
        cout << "\n this model not found , try agin متقرفناش \n";
    }






    plane_list.push_back(*ptr);//add values from dynamic var to vector 

    //delete dynamic var 
    delete ptr;
    ptr = NULL;


}

void update_plane()
{
    bool search = false;
    bool model_found = false;
    int input_code;
    cout << "\n Enter the code of the plane you want to modify : \n";
    cin >> input_code;
    for (int i = 0; i < plane_list.size(); i++)
    {
        if (input_code == plane_list[i].plane_code)
        {
            search = true;
            cout << "\n Enter the new plane model : \n ";
            cin >> plane_list[i].plane_model;

            for (int j = 0; j < 5; j++)//عشان نعدل الصفوف والاعمده علي حسب النوع الجديد 
            {
                if (models[j].plane_model == plane_list[i].plane_model)
                {
                    model_found = true;
                    plane_list[i].number_of_rows = models[j].number_of_row;
                    plane_list[i].number_of_col = models[j].number_of_col;
                    plane_list[i].seat_letters = models[j].seat_letters;
                    cout << "\n Enter the new plane code : \n ";
                    cin >> plane_list[i].plane_code;
                    cout << " updated successfully \n";
                    break;
                }
                else
                {
                    model_found = false;
                }

            }


        }


    }

    if (search == false)
    {
        cout << " this code not found  \n";
    }
    else if (model_found == false)
    {
        cout << "\n this model not found   \n";
    }

}


void add_flight()

{

    flight* ptr = new flight();
    int plane_code_for_flight_test;
    bool found = false;

    cout << "\n Enter the code of the plane for this flight :\n ";
    cin >> plane_code_for_flight_test;

    for (int i = 0; i < plane_list.size(); i++)//اللوب دي عشان تدور علي اكواد الطائرات هل الكود الي عايز يربطه بالطاءره ده موجود ولا لا 
    {
        if (plane_list[i].plane_code == plane_code_for_flight_test)
        {
            found = true;
            cout << "\n Enter the flight code :\n ";
            cin >> (*ptr).flight_code;

            ///////////////////////////////////////////

            cout << "\n Enter the departure city :\n ";
            cin >> (*ptr).departure_city;

            cout << "\n Enter the arrival city :\n ";
            cin >> (*ptr).arrival_city;

            ///////////////////////////////////////////////

            cout << "\n Enter the departure airport :\n ";
            cin >> (*ptr).departure_airport;

            cout << "\n Enter the arrival airport :\n ";
            cin >> (*ptr).arrival_airport;

            ///////////////////////////////////////////////////

            cout << "\n Enter the Day of departure date :\n ";
            cin >> (*ptr).departure_date.day;

            cout << "\n Enter the month of departure date :\n ";
            cin >> (*ptr).departure_date.month;

            cout << "\n Enter the Day of arrival date :\n ";
            cin >> (*ptr).arrival_date.day;

            cout << "\n Enter the month of arrival date :\n ";
            cin >> (*ptr).arrival_date.month;

            ////////////////////////////////////////////////////////

            cout << "\n Enter the hours of departure time :\n ";
            cin >> (*ptr).departure_time.hours;

            cout << "\n Enter the minutes of departure time :\n ";
            cin >> (*ptr).departure_time.minutes;

            cout << "\n Enter the hours of arrival time :\n ";
            cin >> (*ptr).arrival_time.hours;

            cout << "\n Enter the minutes of arrival time :\n ";
            cin >> (*ptr).arrival_time.minutes;

            ////////////////////////////////////////////////////////


            (*ptr).for_planecode = plane_list[i].plane_code;//نوصل الرحله بالطائره


            flight_list.push_back(*ptr);//add values from dynamic var to vector 

            //delete dynamic var 
            delete ptr;
            ptr = NULL;

        }
    }
    if (found == false)
    {
        cout << "\n this plane code not found, please add the plane first \n";

    }
    else
    {
        cout << " added successfully \n";
    }





}


void update_flight()
{
    bool search = false;
    bool found = false;
    int input_code;
    int plane_code_for_flight_test;

    cout << "\n Enter the code of the flight you want to modify \n";
    cin >> input_code;
    for (int i = 0; i < flight_list.size(); i++)// تدور علي هل الرحله موجوده 
    {
        if (input_code == flight_list[i].flight_code)
        {
            search = true;
            cout << "\n Enter the new code of the plane for this flight :\n ";
            cin >> plane_code_for_flight_test;

            for (int j = 0; j < plane_list.size(); j++)//اللوب دي عشان تدور علي اكواد الطائرات هل الكود الي عايز يربطه بالطاءره ده موجود ولا لا 
            {
                if (plane_list[j].plane_code == plane_code_for_flight_test)
                {
                    found = true;
                    flight_list[i].for_planecode = plane_list[j].plane_code;//نوصل الرحله بالطائره الجديدة


                    cout << "\n Update the new flight code :\n ";
                    cin >> flight_list[i].flight_code;

                    cout << "\n Update the new departure city :\n ";
                    cin >> flight_list[i].departure_city;

                    cout << "\n Update the new arrival city :\n ";
                    cin >> flight_list[i].arrival_city;



                    cout << "\n Update the new departure airport :\n ";
                    cin >> flight_list[i].departure_airport;

                    cout << "\n Update the arrival airport :\n ";
                    cin >> flight_list[i].arrival_airport;



                    cout << "\n Update the new Day of departure date :\n ";
                    cin >> flight_list[i].departure_date.day;

                    cout << "\n Update the new month of departure date :\n ";
                    cin >> flight_list[i].departure_date.month;

                    cout << "\n Update the new Day of arrival date :\n ";
                    cin >> flight_list[i].arrival_date.day;

                    cout << "\n Update the new month of arrival date :\n ";
                    cin >> flight_list[i].arrival_date.month;



                    cout << "\n Update the new hours of departure time :\n ";
                    cin >> flight_list[i].departure_time.hours;

                    cout << "\n Update the new minutes of departure time :\n ";
                    cin >> flight_list[i].departure_time.minutes;

                    cout << "\n Update the new hours of arrival time :\n ";
                    cin >> flight_list[i].arrival_time.hours;

                    cout << "\n Update the new minutes of arrival time :\n ";
                    cin >> flight_list[i].arrival_time.minutes;

                }
            }





        }
    }
    if (search == false || found == false)
    {
        cout << " this code not found  \n";
    }

}



void search_plane()//function to search for plane by its code by admins.
{
    int search_plane_code;
    int printed_index = -100;//اي رقم عشان اتحقق بس يارجاله

    cout << "\n Search the plane code : \n";
    cin >> search_plane_code;

    for (int i = 0; i < plane_list.size(); i++)
    {
        if (plane_list[i].plane_code == search_plane_code)
        {
            printed_index = i;
            break;
        }
    }
    if (printed_index == -100)
    {
        cout << "\n this code not found \n";
    }
    else
    {
        cout << "\n Airplane information : \n";


        cout << "\n plane model :  ";
        cout << plane_list[printed_index].plane_model;

        cout << "\n plane code :  ";
        cout << plane_list[printed_index].plane_code;

        cout << "\n  number of Rows :  ";
        cout << plane_list[printed_index].number_of_rows;

        cout << "\n the seat_letters : ";
        cout << plane_list[printed_index].seat_letters;
    }


}



void search_flight()
{
    int Search_flight_code;
    int printed_index;

    cout << "\n Search the flight code : ";
    cin >> Search_flight_code;

    for (int i = 0; i < flight_list.size(); i++)
    {
        if (flight_list[i].flight_code == Search_flight_code)
        {
            printed_index = i;
            break;

        }
        else
        {
            printed_index = -100;//اي رقم عشان اتحقق بس يارجاله
        }
    }

    if (printed_index == -100)
    {
        cout << "\n this code not found \n";
    }
    else
    {
        cout << "\n  the departure city : ";
        cout << flight_list[printed_index].departure_city;

        cout << "\n  the arrival city : ";
        cout << flight_list[printed_index].arrival_city;


        cout << "\n  the departure airport : ";
        cout << flight_list[printed_index].departure_airport;

        cout << "\n  the arrival airport : ";
        cout << flight_list[printed_index].arrival_airport;


        cout << "\n  the date of  departure (day:month) : ";
        cout << flight_list[printed_index].departure_date.day << ":";
        cout << flight_list[printed_index].departure_date.month;

        cout << "\n  the arrival date (day:month) : ";
        cout << flight_list[printed_index].arrival_date.day << ":";
        cout << flight_list[printed_index].arrival_date.month;


        cout << "\n  the time of departure (hours:minutes) : ";
        cout << flight_list[printed_index].departure_time.hours << ":";
        cout << flight_list[printed_index].departure_time.minutes;

        cout << "\n  the time of arrival (hours:minutes) : ";
        cout << flight_list[printed_index].arrival_time.hours << ":";
        cout << flight_list[printed_index].arrival_time.minutes;


        cout << "\n  the Flight code : ";
        cout << flight_list[printed_index].flight_code;

        cout << "\n  the plane code for this flight : ";
        cout << flight_list[printed_index].for_planecode;

    }


}


bool login()
{
    string username, password, choose_again;


    do
    {
        cout << "\n Please enter your username : \n";
        cin >> username;
        cout << "\n Please enter your password : \n";
        cin >> password;
        for (int i = 0; i < 10; i++)
        {
            if (username == admins[i].username && password == admins[i].password)
            {
                return true;
            }

        }

        cout << "\n  wrong password or username, Do you want to try again ? \n ";

        cout << "\n    Yes   <======>   NO  \n";

        cin >> choose_again;

    } while (choose_again == "Yes" || choose_again == "yes");
    return false;

}




void admin_path()
{


    // مجرد ارقام تجربه 
    admins[0].username = "m";
    admins[0].password = "m@123";
    admins[1].username = "mohamedhany";
    admins[1].password = "mohamedhany@123";



    if (login() == true)
    {
        int choose_operation;
        cout << "\n Welcome Admin \n";
        cout << "\n Please choose the operation you want to do : \n";
        cout << "\n    1. Add plane \n    2. Update plane \n    3. Add flight \n    4. Update flight \n";
        cin >> choose_operation;
        switch (choose_operation)
        {
        case 1:
            add_plane();
            break;
        case 2:
            update_plane();
            break;
        case 3:
            add_flight();
            break;
        case 4:
            update_flight();
            break;
        default:
            cout << "\n Invalid input \n";
            break;
        }
    }
    else
    {
        cout << "\n Invalid username or password \n";
        admin_path();
    }



}


void start()
{
    //مجرد ارقام للتجربه 
    plane_list[0].plane_model = "Boeing747";
    plane_list[0].number_of_rows = 12;
    plane_list[0].plane_code = 77;


    // مجرد ارقام تجربه 
    flight_list[0].departure_city = "cairo";
    flight_list[0].arrival_city = "Paris";
    flight_list[0].departure_airport = "cairo_air";
    flight_list[0].arrival_airport = "Roissy";
    flight_list[0].departure_date.day = 4;
    flight_list[0].departure_date.month = "march";
    flight_list[0].arrival_date.day = 4;
    flight_list[0].arrival_date.month = "march";
    flight_list[0].departure_time.hours = 4;
    flight_list[0].departure_time.minutes = 0;
    flight_list[0].arrival_time.hours = 6;
    flight_list[0].arrival_time.minutes = 30;
    flight_list[0].flight_code = 606;
    //باقي الكراسي هعملهم  لما ادقن المصفوفه الديناميكيه




    string choose_again;
    string choose;//admin or user


    do
    {
        cout << "\n Please choose if you are an admin or a user : \n";
        cin >> choose;
        if (choose == "admin" || choose == "Admin")
        {
            admin_path();
        }
        else if (choose == "user" || choose == "User")
        {
            cout << "\n Welcome User \n";

        }
        else
        {
            cout << "\n Invalid input \n";
        }


        cout << "\n Do you want to do another operation ? \n ";

        cout << "\n    Yes   <======>   NO  \n";

        cin >> choose_again;

    } while (choose_again == "Yes" || choose_again == "yes");
    exit(0);

}