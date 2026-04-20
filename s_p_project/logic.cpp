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
    cout << "\n Enter the plane model : \n ";
    cin >> (*ptr).plane_model;


    cout << "\n Enter the plane code : \n ";
    cin >> (*ptr).plane_code;


    cout << "\n Enter the number of Rows :\n  ";
    cin >> (*ptr).number_of_rows;


    cout << "\n  add plane is done \n";


    //2d dynamic array of seats 
	(*ptr).seats_p = new char * [(*ptr).number_of_rows];
    for (int i = 0; i < (*ptr).number_of_rows; i++)
    {
        (*ptr).seats_p[i] = new char[10];//10 because we have 10 seats in each row (A,B,C,D,E,F,G,H,J,K)
        for (int j = 0; j < 10; j++)
        {
			(*ptr).seats_p[i][j] = 'O';//O for available seat  >>     //all seats are available at the beginning
		}
	}


    plane_list.push_back(*ptr);//add values from dynamic var to vector 

    //delete dynamic var 
    delete ptr;
    ptr = NULL;


}

void update_plane()
{
    bool search = false;
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


            cout << "\n Enter the new plane code : \n ";
            cin >> plane_list[i].plane_code;

            int old_rows = plane_list[i].number_of_rows;//to check in new number of rows
            
            cout << "\n Enter the new number of Rows :\n  ";
            cin >> plane_list[i].number_of_rows;

            if (old_rows = plane_list[i].number_of_rows)
            {
            }
            else
            {
                for (int j = 0; j < old_rows; j++)
                {
					delete[] plane_list[i].seats_p[j];//delete old rows
                }
                 delete[] plane_list[i].seats_p;//delete old row pointers from memory


				 //2d dynamic array of seats with new number of rows
                 //هكمل هنا ليسا





            }

           


            cout << " updated successfully \n";
        }


    }
    if (search == false)
    {
        cout << " this code not found  \n";
    }

}

void add_flight()

{
    flight* ptr = new flight();
    cout << "\n Enter the flight number :\n ";
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



    flight_list.push_back(*ptr);//add values from dynamic var to vector 

    //delete dynamic var 
    delete ptr;
    ptr = NULL;


}

void update_flight()
{
    bool search = false;
    int input_code;
    cout << "\n Enter the code of the flight you want to modify \n";
    cin >> input_code;
    for (int i = 0; i < flight_list.size(); i++)
    {
        if (input_code == flight_list[i].flight_code)
        {
            search = true;
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



            cout << "\n Update the Flight code \n ";
            cin >> flight_list[i].flight_code;
        }
    }
    if (search == false)
    {
        cout << " this code not found  \n";
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
        for (int i = 0; i < size(admins); i++)
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
    admins[0].username = "mohamedalaa";
    admins[0].password = "mohamedalaa@123";
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