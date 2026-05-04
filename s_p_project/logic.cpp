#include "stdafx.h"
#include "logic.h"
#include "data.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


//gui functions
//new add plane function to use with gui
void add_plane_gui(string model, int code)
{
    plane* ptr = new plane();
    ptr->plane_model = model;
    ptr->plane_code = code;

    for (int i = 0; i < 5; i++) {
        if (models[i].plane_model == ptr->plane_model) {
            ptr->number_of_rows = models[i].number_of_row;
            ptr->number_of_col = models[i].number_of_col;
            ptr->seat_letters = models[i].seat_letters;
        }
    }
    plane_list.push_back(*ptr);
    delete ptr;
}
//----------------------------------------------------------------
bool add_flight_gui(int planecode, int flightcode, string depCity, string arrCity, string depAirport, string arrAirport,
    int depDay, string depMonth, int arrDay, string arrMonth, int depHour, int depMinute, int arrHour, int arrMinute)

{
    flight* ptr = new flight();
    bool found = false;

    for (int i = 0; i < plane_list.size(); i++)
    {
        if (plane_list[i].plane_code == planecode)
        {
            found = true;
            ptr->flight_code = flightcode;
            ptr->departure_city = depCity;
            ptr->arrival_city = arrCity;
            ptr->departure_airport = depAirport;
            ptr->arrival_airport = arrAirport;

            ptr->departure_date.day = depDay;
            ptr->departure_date.month = depMonth;

            ptr->arrival_date.day = arrDay;
            ptr->arrival_date.month = arrMonth;

            ptr->departure_time.hours = depHour;
            ptr->departure_time.minutes = depMinute;

            ptr->arrival_time.hours = arrHour;
            ptr->arrival_time.minutes = arrMinute;

            // 4. أهم خطوة: بنربط الرحلة دي بكود الطيارة اللي لقيناها
            ptr->for_planecode = plane_list[i].plane_code;

            // 5. بنضيف الرحلة الجديدة في لستة الرحلات الأساسية
            flight_list.push_back(*ptr);

            // بنوقف اللوب خلاص ملناش دعوة بباقي الطيارات
            break;
        }
    }
    delete ptr;
    return found;
}
//--------------------------------------------------------------------------

void user_login_gui(string name,string passport)
{
    current_user.username = name;
    current_user.passport_id = passport;
}



//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

//backend functions(admin)
void add_plane()
{
    plane* ptr = new plane();
    bool model_found = false;
    cout << "\n Enter the plane model : \n ";
    cin >> (*ptr).plane_model;

    for (int i = 0; i < size(models); i++)//اللووب دي عشان تربط وتحط الصفوف والاعمده بتاعت نوع الطياره الي الادمن دخلها 
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
        cout << "\n this model not found ,\n";
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

            for (int j = 0; j < flight_list.size(); j++)//للتأكد بس لو فيه مقعد محجوز فيه رحله والرحله دي هتتعمل بالطياره دي مش هيقدر يعدل 
            {
                if (flight_list[j].for_planecode == plane_list[i].plane_code && flight_list[j].is_empty == false)
                {

                    cout << "\n Cannot modify: There are already bookings for flights using this plane!\n";
                    return;//دي كدا هيخرج من الفانكشن يارجاله 
                }
            }


            search = true;
            cout << "\n Enter the new plane model : \n ";
            cin >> plane_list[i].plane_model;

            for (int j = 0; j < size(models); j++)//عشان نعدل الصفوف والاعمده علي حسب النوع الجديد 
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


int time_of_flight_to_minutes(mytime t)//دي بتحول وقت الرحله الي دقايق عشان اتشيك علي تعارض الاوقات عند اضافه رحله جديده
{
    return t.hours * 60 + t.minutes;
}


bool is_plane_available(int pCode, int dDay, string dMonth, int dHour, int dMin, int aHour, int aMin)//دي الفانكشن الاساسيه الي بتشيك علي تعارض الوقت 
{
    for (int i = 0; i < flight_list.size(); i++)

    {
        if (flight_list[i].for_planecode == pCode && flight_list[i].departure_date.day == dDay && flight_list[i].departure_date.month == dMonth)
        {
            int existing_start = time_of_flight_to_minutes(flight_list[i].departure_time);
            int existing_end = time_of_flight_to_minutes(flight_list[i].arrival_time);
            int new_start = dHour * 60 + dMin;
            int new_end = aHour * 60 + aMin;
            //الكونديشن ده معقد يارب اكون ظبطه 
            if ((new_start >= existing_start && new_start <= existing_end) ||
                (new_end >= existing_start && new_end <= existing_end) ||
                (new_start <= existing_start && new_end >= existing_end))
            {
                return false; //كدا فيه تضارب في الوقت بتاع الرحله الي دخلتها للفانكشن 
            }
        }
    }
    return true;
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
            //نأخد شويه بيانات عشان نعمل بيها تشيك الاول
            cout << "\n Enter the Day of departure date :\n ";
            cin >> (*ptr).departure_date.day;

            cout << "\n Enter the month of departure date :\n ";
            cin >> (*ptr).departure_date.month;


            cout << "\n Enter the hours of departure time :\n ";
            cin >> (*ptr).departure_time.hours;

            cout << "\n Enter the minutes of departure time :\n ";
            cin >> (*ptr).departure_time.minutes;

            cout << "\n Enter the hours of arrival time :\n ";
            cin >> (*ptr).arrival_time.hours;

            cout << "\n Enter the minutes of arrival time :\n ";
            cin >> (*ptr).arrival_time.minutes;

            //نتشيك بقا هنا 
            if (!is_plane_available(plane_code_for_flight_test, (*ptr).departure_date.day, (*ptr).departure_date.month,
                (*ptr).departure_time.hours, (*ptr).departure_time.minutes,
                (*ptr).arrival_time.hours, (*ptr).arrival_time.minutes))
            {
                cout << "\n [!] Error: This plane is busy with another flight at the same time!\n";
                delete ptr;
                return;
            }
            //نكمل ملئ البيانات لو مفيش تعارض 
            cout << "\n Enter the flight code :\n ";
            cin >> (*ptr).flight_code;

            cout << "\n Enter the departure city :\n ";
            cin >> (*ptr).departure_city;

            cout << "\n Enter the arrival city :\n ";
            cin >> (*ptr).arrival_city;

            cout << "\n Enter the departure airport :\n ";
            cin >> (*ptr).departure_airport;

            cout << "\n Enter the arrival airport :\n ";
            cin >> (*ptr).arrival_airport;

            cout << "\n Enter the Day of arrival date :\n ";
            cin >> (*ptr).arrival_date.day;

            cout << "\n Enter the month of arrival date :\n ";
            cin >> (*ptr).arrival_date.month;

            (*ptr).for_planecode = plane_list[i].plane_code;//نوصل الرحله بالطائره
            (*ptr).rows_number = plane_list[i].number_of_rows;
            (*ptr).columns_number = plane_list[i].number_of_col;


            for (int row = 0; row < plane_list[i].number_of_rows; row++)// ده الي بيملي كراسي كل رحله مؤقتا كدا كدا هتتظبط في الواجهه
            {
                for (int col = 0; col < plane_list[i].number_of_col; col++)
                {
                    (*ptr).seats[row][col] = 'E';
                }
                cout << " " << endl;
            }

            flight_list.push_back(*ptr);//add values from dynamic var to vector 

            //delete dynamic var 
            delete ptr;
            ptr = NULL;

        }
    }
    if (found == false)
    {
        cout << "\n this plane code not found, please add the plane first \n";
        //delete dynamic var /*عملتها هنا عشان لو متخلش جوا اصلا يمسح بردو البوينتر ويخليه مش بيشاور علي حاجه *\
        delete ptr;
        ptr = NULL;
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
            if (flight_list[i].is_empty == false)
            {
                cout << "\n Error: Cannot update this flight. Tickets are already booked!\n";
                return;
            }
            search = true;
            cout << "\n Enter the new code of the plane for this flight :\n ";
            cin >> plane_code_for_flight_test;

            if (plane_code_for_flight_test == flight_list[i].for_planecode)
            {
                for (int j = 0; j < plane_list.size(); j++)//اللوب دي عشان تدور علي اكواد الطائرات هل الكود الي عايز يربطه بالطاءره ده موجود ولا لا 
                {
                    if (plane_list[j].plane_code == plane_code_for_flight_test)
                    {
                        found = true;
                        flight_list[i].for_planecode = plane_list[j].plane_code;//نوصل الرحله بالطائره الجديدة
                        flight_list[i].rows_number = plane_list[j].number_of_rows;
                        flight_list[i].columns_number = plane_list[j].number_of_col;


                        for (int row = 0; row < plane_list[i].number_of_rows; row++)//ده بيملي حاله الكراسي بالحجم الجديد للطياره 
                        {
                            cout << row + 1 << " ";
                            for (int col = 0; col < plane_list[i].number_of_col; col++)
                            {
                                flight_list[i].seats[row][col] = 'E';
                            }
                            cout << " " << endl;
                        }


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



void search_flight_admin()
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


bool admin_login()
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

    if (admin_login() == true)
    {
        int choose_operation;
        cout << "\n Welcome Admin \n";
        cout << "\n Please choose the operation you want to do : \n";
        cout << "\n    1. Add plane \n    2. Update plane \n    3. Add flight \n    4. Update flight \n    5. Search plane \n    6. Search flight \n";
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
        case 5:
            search_plane();
            break;
        case 6:
            search_flight_admin();
            break;
        default:
            cout << "\n Invalid input \n";
            break;
        }
    }
    else
    {
        cout << "\n Invalid username or password \n";
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//



//backend functions(user)
void Display_Flight(flight details)
{
    cout << "\n=======================================================================================\n";
    cout << "** Flight Details **";
    cout << "\nFrom: " << details.departure_city << "\nTo: " << details.arrival_city;
    cout << "\ndeparture airport: " << details.departure_airport;
    cout << "\nArrival airport: " << details.arrival_airport;
    cout << "\n------------------------------------------------------------------------------------------";
    cout << "\nDeparture date: " << details.departure_date.day << " " << details.departure_date.month;
    cout << "\nArrival date: " << details.arrival_date.day << " " << details.arrival_date.month;
    cout << "\n------------------------------------------------------------------------------------------";
    cout << "\ndeparture time: " << details.departure_time.hours << ":" << details.departure_time.minutes;
    cout << "\narrival time: " << details.arrival_time.hours << ":" << details.arrival_time.minutes;
    cout << "\n=======================================================================================\n";
}

void user_login()
{
    cout << "Enter Username: ";
    cin >> current_user.username;

    cout << "\nEnter your passport number: ";
    cin >> current_user.passport_id;

    cout << "---------------------------------------------------------------------------------------------\n";
}

int Search_Ways_Menu()
{
    while (true)
    {
        cout << "*[Flight Search]*" << "\n";
        cout << "Search by: " << "\n";
        cout << "=======================================================================================\n";
        cout << "1.Departure City\n" << "2.Arrival City\n" << "3.date\n";
        cout << "=======================================================================================";
        cout << "\nEnter choice: ";

        if (!(cin >> choice))
        {

            cout << "\n[!] Error: Please enter a NUMBER (1, 2, or 3), not letters.\n";

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "---------------------------------------------------------------------------------------\n";
            continue;
        }


        if (choice >= 1 && choice <= 3)
        {
            return choice;
        }
        else
        {
            cout << "Invalid choice! please enter 1, 2 or 3\n";
            cout << "---------------------------------------------------------------------------------------\n";
        }
    }
}//دي مجرد انها بس بترجع الرقم الي بيدل علي هو هيبحث بأي   

string Checking_City_Letters(string city)//بتشيك ان الحروف كبيره ولا صغيره 
{
    if (city.empty())
        return city;


    for (int i = 0; i < city.length(); i++)
    {
        city[i] = tolower(city[i]);
    }

    return city;

}

void Checking_Date()
{
    int maxdays = 31;
    bool TrueMonth = false;

    while (!TrueMonth)
    {
        cout << "Enter Month (WORD ONLY please): ";
        cin >> months;

        for (int i = 0; i < months.length(); i++)
        {
            months[i] = tolower(months[i]);
        }

        if (months == "january" || months == "march" || months == "may" || months == "july" ||
            months == "august" || months == "october" || months == "december")
        {
            maxdays = 31;
            TrueMonth = true;
        }
        else if (months == "april" || months == "june" || months == "september" || months == "november")
        {
            maxdays = 30;
            TrueMonth = true;
        }
        else if (months == "february")
        {
            maxdays = 28;
            TrueMonth = true;
        }
        else
        {
            cout << "[!] Error: Invalid month name. Please write the word (e.g., 'March').\n";
        }
    }

    cout << "Enter Day (1=>" << maxdays << "): ";
    while (!(cin >> days) || days < 1 || days > maxdays) {
        cout << "Invalid day for " << months << "! Please enter a number between 1 and " << maxdays << ": ";
        cin.clear();
        cin.ignore(100, '\n');
    }

}

void Keyword_Search(int choice)
{

    switch (choice)
    {
    case 1:
        cout << "Enter Departure City: ";
        cin.ignore();
        getline(cin, keyword);
        keyword = Checking_City_Letters(keyword);
        search_Flights(1);
        break;
    case 2:
        cout << "\nEnter Arrival City: ";
        cin.ignore();
        getline(cin, keyword);
        keyword = Checking_City_Letters(keyword);
        search_Flights(2);
        break;
    case 3:
        cin.ignore();
        cout << "\nEnter Departure date";
        Checking_Date();
        search_Flights(3);
        break;
    }

}


void search_Flights(int choice)
{


    int code;
    int found_flight = 0;
    bool match = false;
    for (int i = 0; i < flight_list.size(); i++)// دي الي بتبحث في الفيكتور 
    {
        bool match = false;

        string dep_city = Checking_City_Letters(flight_list[i].departure_city);
        string arr_city = Checking_City_Letters(flight_list[i].arrival_city);
        string flight_month = Checking_City_Letters(flight_list[i].departure_date.month);


        if (choice == 1 && dep_city == keyword)
            match = true;

        else if (choice == 2 && arr_city == keyword)
            match = true;

        else if (choice == 3 && flight_month == months && flight_list[i].departure_date.day == days)
            match = true;

        if (match)
        {
            found_flight++;
            cout << "---------------------------------------------------------------------------------------\n";
            cout << "--- Flight Found ---\n";
            cout << "From: " << flight_list[i].departure_city << "\nTo: " << flight_list[i].arrival_city;
            cout << "\nDeparture date: " << flight_list[i].departure_date.day << " " << flight_list[i].departure_date.month;
            cout << "\nflight code: " << flight_list[i].flight_code;
            cout << "\n---------------------------------------------------------------------------------------\n";
        }


    }
    if (found_flight == 0)
    {
        cout << "\n[!] Sorry, no flights found matching your search.\n";
    }
    if (found_flight > 0)
    {

        cout << "Do you want to show specific flight details (Yes/No): ";
        cin >> details_choice;

        if (details_choice == "Yes" || details_choice == "yes")
        {
            bool code_found = false;
            do {
                cout << "Enter flight code: ";
                if (!(cin >> code)) {
                    cout << "[!] Invalid input! Please enter numbers only.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                for (int i = 0; i < flight_list.size(); i++)
                {
                    if (flight_list[i].flight_code == code)
                    {
                        current_flight_index = i;
                        Display_Seats(flight_list[current_flight_index]);
                        current_flight_index = i;
                        currentFlight = flight_list[i];
                        code_found = true;
                    }
                }

                if (!code_found)
                {
                    cout << "[!] Wrong flight code. Try again.\n";
                }

            } while (!code_found);
        }

    }
}


void Display_Seats(flight current_flight)
{
    cout << "   ";
    for (int col = 0; col < current_flight.columns_number; col++)//هنا استخدمت الاسكي عشان اطبع حروف علي حسب عدد الاعمده
    {
        cout << char('A' + col) << " ";
    }
    cout << endl;

    for (int row = 0; row < current_flight.rows_number; row++)
    {
        cout << row + 1 << (row + 1 < 10 ? "  " : " ");
        for (int col = 0; col < current_flight.columns_number; col++)
        {
            cout << current_flight.seats[row][col] << " ";
        }
        cout << endl;
    }
}

void book_Seats()
{
    string row;
    flight_list[current_flight_index].is_empty = false;//عشان لو حد عايز يعدل الرحله دي ميقدرش لان فيها حجوزات مهمه دي 
    cout << "           enter your seat please      " << endl;
    cout << "enter row from 1 to " << currentFlight.rows_number << " please" << endl;
    cin >> row;
    cin.ignore(100, '\n');

    int user_row = stoi(row);
    if (user_row >= 1 && user_row <= currentFlight.rows_number)
    {
        cout << "enter your colum from A to " << char('A' + currentFlight.columns_number - 1) << " please" << endl;
        cin >> user_colum;
        cin.ignore(100, '\n');
        user_colum = toupper(user_colum);
        indexColum = user_colum - 'A';
        indexRow = user_row - 1;

        if (flight_list[current_flight_index].seats[indexRow][indexColum] == 'E')
        {
            flight_list[current_flight_index].seats[indexRow][indexColum] = 'B';

            currentFlight.seats[indexRow][indexColum] = 'B';//عشان يتخزن انه اتحجز عشان لو عايز اطبع المره الجايه

            ticket* t = new ticket;// ده مؤقت 
            (*t).passenger_name = current_user.username;
            (*t).passport_id = current_user.passport_id;
            (*t).seat_row = user_row;
            (*t).seat_letter = user_colum;
            (*t).departure_city = currentFlight.departure_city;
            (*t).arrival_city = currentFlight.arrival_city;
            (*t).date.day = currentFlight.departure_date.day;
            (*t).date.month = currentFlight.departure_date.month;
            (*t).time.hours = currentFlight.departure_time.hours;
            (*t).time.minutes = currentFlight.departure_time.minutes;

            tickets_list.push_back(*t);

            cout << ">>> Seat booked successfully!" << endl;
            cout << "\n--- YOUR TICKET ---\nName: " << (*t).passenger_name << "\nID: " << (*t).passport_id
                << "\nRoute: " << (*t).departure_city << " to " << (*t).arrival_city
                << "\nSeat: " << (*t).seat_row << (*t).seat_letter << "\nTime: " << (*t).time.hours << ":" << (*t).time.minutes << "\nDate: " << (*t).date.day << " " << (*t).date.month << endl;
        }
        else if (user_row < 1 || user_row > currentFlight.rows_number || user_colum < 'A' || user_colum > char('A' + currentFlight.columns_number - 1))
        {
            cout << "Invalid input!" << endl;
        }
        else
            cout << "this chair is already taken" << endl;
    }

};

void see_ticket()
{
    string cancel;
    bool found = false;
    for (int i = 0; i < tickets_list.size(); i++)
    {
        if (tickets_list[i].passport_id == current_user.passport_id)
        {
            found = true;
            cout << "\n--- YOUR TICKET ---\nName: " << tickets_list[i].passenger_name << "\nID: " << tickets_list[i].passport_id
                << "\nRoute: " << tickets_list[i].departure_city << " to " << tickets_list[i].arrival_city
                << "\nDate: " << tickets_list[i].date.day << " " << tickets_list[i].date.month
                << "\nTime: " << tickets_list[i].time.hours << ":" << tickets_list[i].time.minutes
                << "\nSeat: " << tickets_list[i].seat_row << tickets_list[i].seat_letter << endl;
            cout << "   \nDo you want to cancel this booking? (Yes/No): ";
            cin >> cancel;
            if (cancel == "Yes" || cancel == "yes")
            {
                //for (int j = 0; j < flight_list.size(); j++)//دي الي بترجع الكرسي فاضي لما يكنسل الحجز 
                //{
                //    if (flight_list[j].flight_code == tickets_list[i].flight_number)
                //    {
                //        flight_list[j].seats[tickets_list[i].seat_row - 1][tickets_list[i].seat_letter - 'A'] = 'E';
                //        break;
                //    }
                //}
                flight_list[current_flight_index].seats[tickets_list[i].seat_row - 1][tickets_list[i].seat_letter - 'A'] = 'E';
                tickets_list.erase(tickets_list.begin() + i);
                cout << ">>> Booking cancelled successfully!" << endl;
            }
            else if (cancel == "No" || cancel == "no")
            {

            }
            else
            {
                cout << "Invalid input!" << endl;
            }


        }
    }
    if (!found)
    {
        cout << "\nNo ticket found for your passport ID.\n";
    }
}


void user_path()
{
    user_login();
    char user_choice;
    cout << "\n Please choose the operation you want to do : (start searching >> s , see your ticket >> t)\n";
    cin >> user_choice;
    if (user_choice == 's' || user_choice == 'S')
    {

        bool search_again = true;
        while (search_again)
        {
            Search_Ways_Menu();// return number to search by it
            Keyword_Search(choice);
            if (details_choice == "Yes" || details_choice == "yes")
            {
                cout << "\nDo you want to book ticket from this flight ? (Y/N) ";
                string back;
                cin >> back;

                if (back == "yes" || back == "Yes")
                {
                    Display_Seats(currentFlight);
                    book_Seats();
                    return;
                }
                else
                {
                    search_again = false;
                }
            }
            else
            {
                search_again = false;
            }
        }
    }
    else if (user_choice == 't' || user_choice == 'T')
    {
        see_ticket();
    }
    else
    {
        cout << "\n Invalid input \n";
    }
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//



void start()
{
    
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
            user_path();
        }
        else
        {
            cout << "\n Invalid input \n";
        }


        cout << "\n Do you want to do another operation ? \n ";

        cout << "\n    Yes   <======>   NO  \n";

        cin >> choose_again;

    } while (choose_again == "Yes" || choose_again == "yes");


}

//----------------------file handling functions----------------------//
void loadAdmins()
{
    ifstream infile("admins.txt");

    if (infile.is_open())
    {
        int admin_count = 0;
        while (infile >> admins[admin_count].username >> admins[admin_count].password)
        {
            admin_count++;
            if (admin_count == 10)
            {
                cout << "Admins limit reached. Cannot load more admins." << endl;
                break;
            }
            infile.ignore();
        }
        infile.close();
        cout << "Admins loaded successfully. Total admins : " << admin_count << endl;
    }
    else
    {
        cout << "Unable to open \"admins.txt\" for reading." << endl;
    }
}

void saveAdmins(admin admins[])
{
    ofstream outfile("admins.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < 3; i++)
        {
            outfile << admins[i].username << " "
                << admins[i].password << endl;
        }
        outfile.close();
        cout << "Admins saved successfully." << endl;
    }
    else
    {
        cout << "Unable to open \"admins.txt\" for writing." << endl;
    }
}

void loadPlanes()
{
    ifstream infile("planes.txt");

    if (infile.is_open())
    {
        plane temp;
        plane_list.clear();

        while (infile >> temp.plane_model >> temp.plane_code >> temp.number_of_rows >> temp.number_of_col >> temp.seat_letters)
        {
            plane_list.push_back(temp);
        }
        infile.close();
        cout << "Planes loaded successfully. Total planes : " << plane_list.size() << endl;
    }
    else
    {
        cout << "Unable to open \"planes.txt\" for reading." << endl;
    }
}

void savePlanes(vector<plane> planes_to_save)
{
    ofstream outfile("planes.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < planes_to_save.size(); i++)
        {
            outfile << planes_to_save[i].plane_model << " "
                << planes_to_save[i].plane_code << " "
                << planes_to_save[i].number_of_rows << " "
                << planes_to_save[i].number_of_col << " "
                << planes_to_save[i].seat_letters << endl;
        }
        outfile.close();
        cout << "Planes saved successfully." << endl;
    }
    else
    {
        cout << "Unable to open \"planes.txt\" for writing." << endl;
    }
}

void loadFlights()
{
    ifstream infile("flights.txt");
    if (infile.is_open())
    {
        flight_list.clear();
        flight temp;

        while (infile >> temp.flight_code >> temp.departure_date.day >> temp.departure_date.month >> temp.arrival_date.day >> temp.arrival_date.month >> temp.departure_time.hours >> temp.departure_time.minutes >> temp.arrival_time.hours >> temp.arrival_time.minutes >> temp.for_planecode >> temp.rows_number >> temp.columns_number)
        {

            temp.is_empty = true;
            getline(infile >> ws, temp.departure_city);
            getline(infile >> ws, temp.arrival_city);
            getline(infile >> ws, temp.departure_airport);
            getline(infile >> ws, temp.arrival_airport);
            for (size_t i = 0; i < temp.rows_number; i++)
            {
                for (size_t j = 0; j < temp.columns_number; j++)
                {
                    infile >> temp.seats[i][j];

                    if (temp.seats[i][j] != 'E')
                    {
                        temp.is_empty = false;
                    }
                }
            }
            flight_list.push_back(temp);
        }
        infile.close();
        cout << "Flights loaded successfully. Total flights : " << flight_list.size() << endl;
    }
    else
    {
        cout << "Unable to open \"flights.txt\" for reading." << endl;
    }
}

void saveFlights(vector<flight> flights_to_save)
{
    ofstream outfile("flights.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < flights_to_save.size(); i++)
        {
            outfile << flights_to_save[i].flight_code << " "
                << flights_to_save[i].departure_date.day << " "
                << flights_to_save[i].departure_date.month << " "
                << flights_to_save[i].arrival_date.day << " "
                << flights_to_save[i].arrival_date.month << " "
                << flights_to_save[i].departure_time.hours << " "
                << flights_to_save[i].departure_time.minutes << " "
                << flights_to_save[i].arrival_time.hours << " "
                << flights_to_save[i].arrival_time.minutes << " "
                << flights_to_save[i].for_planecode << " "
                << flights_to_save[i].rows_number << " "
                << flights_to_save[i].columns_number << endl;

            outfile << flights_to_save[i].departure_city << endl;
            outfile << flights_to_save[i].arrival_city << endl;
            outfile << flights_to_save[i].departure_airport << endl;
            outfile << flights_to_save[i].arrival_airport << endl;
            for (size_t k = 0; k < flights_to_save[i].rows_number; k++)
            {
                for (size_t j = 0; j < flights_to_save[i].columns_number; j++)
                {
                    outfile << flights_to_save[i].seats[k][j] << " ";
                }
                outfile << endl;
            }
        }
        outfile.close();
        cout << "Flights saved successfully." << endl;
    }
    else
    {
        cout << "Unable to open \"flights.txt\" for writing." << endl;
    }
}

void loadTickets()
{
    ifstream infile("tickets.txt");
    if (infile.is_open())
    {
        tickets_list.clear();
        ticket temp;

        while (infile >> temp.flight_number >> temp.date.day >> temp.date.month >> temp.time.hours >> temp.time.minutes >> temp.seat_row >> temp.seat_letter)
        {
            getline(infile >> ws, temp.passenger_name);
            getline(infile >> ws, temp.passport_id);
            getline(infile >> ws, temp.departure_city);
            getline(infile >> ws, temp.arrival_city);

            tickets_list.push_back(temp);
        }
        infile.close();
        cout << "Tickets loaded successfully. Total tickets : " << tickets_list.size() << endl;
    }
    else
    {
        cout << "Unable to open \"tickets.txt\" for reading." << endl;
    }
}

void saveTickets(vector<ticket> tickets_to_save)
{
    ofstream outfile("tickets.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < tickets_to_save.size(); i++)
        {
            outfile << tickets_to_save[i].flight_number << " "
                << tickets_to_save[i].date.day << " "
                << tickets_to_save[i].date.month << " "
                << tickets_to_save[i].time.hours << " "
                << tickets_to_save[i].time.minutes << " "
                << tickets_to_save[i].seat_row << " "
                << tickets_to_save[i].seat_letter << endl;

            outfile << tickets_to_save[i].passenger_name << endl;
            outfile << tickets_to_save[i].passport_id << endl;
            outfile << tickets_to_save[i].departure_city << endl;
            outfile << tickets_to_save[i].arrival_city << endl;
        }
        outfile.close();
        cout << "Tickets saved successfully." << endl;
    }
    else
    {
        cout << "Unable to open \"tickets.txt\" for writing." << endl;
    }
}

void loadPlanes_Models()
{
    ifstream infile("models.txt");

    if (infile.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            infile >> models[i].plane_model >> models[i].number_of_row >> models[i].number_of_col >> models[i].seat_letters;
        }
        infile.close();
        cout << "Models loaded successfully." << endl;
    }
    else
    {
        cout << "Unable to open \"models.txt\" for reading." << endl;
    }
}

void savePlanes_Models(model_of_plane models[])
{
    ofstream outfile("models.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            outfile << models[i].plane_model << " "
                << models[i].number_of_row << " "
                << models[i].number_of_col << " "
                << models[i].seat_letters << endl;
        }
        outfile.close();
        cout << "Models saved successfully." << endl;
    }
    else
    {
        cout << "Unable to open \"models.txt\" for writing." << endl;
    }
}

void initializeDefaultModels()
{
    models[0] = { "EmbraerE190", 20, 8, "ABCD" };
    models[1] = { "Boeing737", 30, 6, "ABCDEF" };
    models[2] = { "AirbusA320", 28, 6, "ABCDEF" };
    models[3] = { "Boeing777", 45, 9, "ABCDEFGHI" };
    models[4] = { "AirbusA380", 60, 10, "ABCDEFGHIJ" };
}

void initializeDefaultPlanes()
{
    for (int i = 0; i < 10; i++)
    {
        plane p;

        int model_index = i % 5;

        p.plane_model = models[model_index].plane_model;
        p.plane_code = 100 + i;
        p.number_of_rows = models[model_index].number_of_row;
        p.number_of_col = models[model_index].number_of_col;
        p.seat_letters = models[model_index].seat_letters;

        plane_list.push_back(p);
    }
}

void initializeDefaultFlights()
{
    srand(time(0));
    flight_list.clear();

    string cities[] = { "Cairo", "Dubai", "Paris", "London", "Rome", "NewYork", "Tokyo", "Madrid", "Riyadh", "Berlin" };
    string airports[] = { "CAI_Intl", "DXB_Intl", "CDG_Paris", "LHR_Heathrow", "FCO_Rome", "JFK_Airport", "HND_Tokyo", "MAD_Barajas", "RUH_KingKhalid", "BER_Brandenburg" };
    string months[] = { "January", "February", "May", "November" };

    int base_flight_code = 500;

    for (int i = 0; i < 20; i++)
    {
        flight f;

        base_flight_code += (rand() % 10) + 1;
        f.flight_code = base_flight_code;

        f.departure_city = cities[i % 10];
        f.arrival_city = cities[(i + 1) % 10];
        f.departure_airport = airports[i % 10];
        f.arrival_airport = airports[(i + 1) % 10];


        int month_index = (i / 5) % 4;
        f.departure_date.day = (rand() % 28) + 1;
        f.departure_date.month = months[month_index];
        f.arrival_date = f.departure_date;


        f.departure_time = { (i % 12) + 1, 0 };
        f.arrival_time = { ((i + 2) % 12) + 1, 30 };


        int plane_index = i % 10;
        f.for_planecode = plane_list[plane_index].plane_code;
        f.rows_number = plane_list[plane_index].number_of_rows;
        f.columns_number = plane_list[plane_index].number_of_col;
        f.is_empty = true;


        for (int r = 0; r < f.rows_number; r++)
        {
            for (int c = 0; c < f.columns_number; c++)
            {
                f.seats[r][c] = 'E';
            }
        }

        flight_list.push_back(f);
    }
}

void initializeDefaultAdmins()
{
    admins[0] = { "sisi", "1234" };
    admins[1] = { "emo", "12345" };
    admins[2] = { "emam", "123456" };
}

void SeedInitialData()// دي لو الفايل فاضي هتنفذ عشان تعمل داتا افتراضيه
{
    ifstream in_models("models.txt");
    if (!in_models.is_open())
    {
        initializeDefaultModels();
    }
    else
    {
        in_models.close();
    }

    ifstream in_planes("planes.txt");
    if (!in_planes.is_open())
    {
        if (plane_list.empty())
        {
            initializeDefaultPlanes();
        }
    }
    else
    {
        in_planes.close();
    }

    ifstream in_flights("flights.txt");
    if (!in_flights.is_open())
    {
        if (flight_list.empty())
        {
            initializeDefaultFlights();
        }
    }
    else
    {
        in_flights.close();
    }

    ifstream in_admins("admins.txt");
    if (!in_admins.is_open())
    {
        initializeDefaultAdmins();
    }
    else
    {
        in_admins.close();
    }
}

void LoadAllData()
{
    SeedInitialData();

    loadAdmins();
    loadPlanes();
    loadFlights();
    loadTickets();
    loadPlanes_Models();

}

void SaveAllData()
{
    saveAdmins(admins);
    savePlanes(plane_list);
    saveFlights(flight_list);
    saveTickets(tickets_list);
    savePlanes_Models(models);
}

