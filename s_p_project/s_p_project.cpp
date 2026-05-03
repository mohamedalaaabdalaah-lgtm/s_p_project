#include "stdafx.h"
#include "s_p_project.h"
#include <QStackedWidget>
#include "logic.h"
#include "data.h"
#include <QDebug>

#include <QMessageBox>


s_p_project::s_p_project(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->showMaximized();
    ui.date_search->hide(); // السطر ده بيخفي مربع التاريخ أول ما الشاشة 
    ui.table_flight_search->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
       
    // set some data

    // دي انواع الطيارات الي عندنا ومش هنعملها فايل  
    models[0].plane_model = "AirbusA320";
    models[0].number_of_row = 20;
    models[0].number_of_col = 6;
    models[0].seat_letters = "ABCHJK";

    models[1].plane_model = "AirbusA330-200";
    models[1].number_of_row = 23;
    models[1].number_of_col = 6;
    models[1].seat_letters = "ABCHJK";

    models[2].plane_model = "AirbusA380-800";
    models[2].number_of_row = 30;
    models[2].number_of_col = 8;
    models[2].seat_letters = "A C D E F G H K";


    models[3].plane_model = "Boeing787-9";
    models[3].number_of_row = 30;
    models[3].number_of_col = 10;
    models[3].seat_letters = "A B C D E F G H J K";

    models[4].plane_model = "AirbusA321";
    models[4].number_of_row = 30;
    models[4].number_of_col = 9;
    models[4].seat_letters = "A B C D E G H J K";

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // مجرد ارقام تجربه 
    admins[0].username = "m";
    admins[0].password = "m@123";
    admins[1].username = "mohamedhany";
    admins[1].password = "mohamedhany@123";

    //مجرد ارقام للتجربه 
    plane_list[0].plane_model = models[3].plane_model;
    plane_list[0].number_of_rows = models[3].number_of_row = 30;
    plane_list[0].number_of_col = models[3].number_of_col = 30;
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

    ui.stackedWidget->setCurrentIndex(0); // welcome page
    ui.lbl_welcome->setText("Welcome to Egypt Airlines");
    ui.btn_enter->setText("Get Started");
    ui.lbl_a_or_u->setText("Are you an Admin or User ?");
    ////table shit/////
    ui.table_flights->setAlternatingRowColors(true);
    ui.table_flights->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.table_planes->setAlternatingRowColors(true);
    ui.table_planes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //////عشان لما نكبر//////
    
    ui.centralWidget->setStyleSheet("background-color: #FFF9F2;");
}

s_p_project::~s_p_project()
{}
//when get started is pressed
void s_p_project::on_btn_enter_clicked()
{
    ui.lbl_welcome->setText("loading...");
    ui.stackedWidget->setCurrentIndex(1);// From Welcome to user/admin
}
void s_p_project::on_btn_choose_user_clicked()
{
    ui.stackedWidget->setCurrentWidget(ui.login_user_page); //users return to welcome page until changes
}

void s_p_project::on_btn_choose_admin_clicked()
{
    ui.stackedWidget->setCurrentWidget(ui.login_page); // go to Login Page
}
//loginpage----------------------------------------
void s_p_project::on_btn_login_submit_clicked()
{
    
    string username = ui.txt_login_username->text().toStdString();
    string pass = ui.txt_login_pass->text().toStdString();

    bool authenticated = false;

    
    for (int i = 0; i < 2; i++) {
        if (username == admins[i].username && pass == admins[i].password) {
            authenticated = true;
            break;
        }
    }

    
    if (authenticated) {
        
        ui.stackedWidget->setCurrentWidget(ui.admin_menu);//from login to menu
    }
    else {
        ui.lbl_error_msg->setText("Wrong password! try again. ");
        ui.lbl_error_msg->setStyleSheet("color: red;");
    }

}
void s_p_project::on_btn_back_admin_clicked()     //   to back login page   //
{

    ui.stackedWidget->setCurrentWidget(ui.login_page);
}


void s_p_project::on_btn_back_login_clicked()     //  to back admin or user   //
{
    
    ui.stackedWidget->setCurrentWidget(ui.admin_or_user);
}


//-----------------------------------------------
void s_p_project::on_btn_addplane_clicked() {
    ui.stackedWidget->setCurrentWidget(ui.addplane_page);//from menu to addplane page
}
void s_p_project::on_btn_save_plane_clicked()
{
    string model = ui.cmb_airplane_model->currentText().toStdString();
    int code = ui.txt_add_code->text().toInt();

    add_plane_gui(model, code);

    QMessageBox::information(this, "Success", "Plane added successfully!");
    ui.cmb_airplane_model->setCurrentIndex(0);
    ui.txt_add_code->clear();
    
}

void s_p_project::on_btn_back_addplane_clicked()    //  back to admin menu   //
{
    
    ui.stackedWidget->setCurrentWidget(ui.admin_menu);
}

//---------------------------------------------------------------------// Add Flight 

void s_p_project::on_btn_add_flight_clicked()
{
    ui.stackedWidget->setCurrentWidget(ui.add_flight_page);
}

void s_p_project::on_btn_save_flight_clicked()
{
    
    //سحب الأكواد
    
    int planecode = ui.txt_plane_code->text().toInt();
    int flightcode = ui.txt_flight_code->text().toInt();


    //سحب المدن والمطارات
    
    string departcity = ui.cmb_depart_city->currentText().toStdString();
    string arrivalcity = ui.cmb_arrival_city->currentText().toStdString();
    string departair = ui.cmb_depart_air->currentText().toStdString();
    string arrivalair = ui.cmb_arrival_air->currentText().toStdString();


    //سحب التواريخ

   
    int depDay = ui.date_depart->date().day();
    int arrDay = ui.date_arrival->date().day();

    // القاموس اللي بيترجم أرقام الشهور لكلمات
    QStringList english_months = { "", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };

    // سحب أرقام الشهور وترجمتها لـ string
    int depMonthNum = ui.date_depart->date().month();
    string depMonthStr = english_months[depMonthNum].toStdString(); // كده بقى جواه مثلا "march"

    int arrMonthNum = ui.date_arrival->date().month();
    string arrMonthStr = english_months[arrMonthNum].toStdString();

    //سحب الوقت 
    int depHour = ui.time_depart->time().hour();
    int depMinute = ui.time_depart->time().minute();
    int arrHour = ui.time_arrival->time().hour();
    int arrMinute = ui.time_arrival->time().minute();

    bool isSuccess = add_flight_gui(planecode, flightcode, departcity, arrivalcity, departair, arrivalair,
        depDay, depMonthStr, arrDay, arrMonthStr, 
        depHour, depMinute, arrHour, arrMinute);

    if (isSuccess == true)
    {
        QMessageBox::information(this, "Success","The trip was successfully added");
        ui.txt_plane_code->clear();
        ui.txt_flight_code->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error","The Plane Code is not available, Add the first Plane.");
    }
}


void s_p_project::on_btn_back_flight_clicked()       //  back to admin menu  //
{
    ui.stackedWidget->setCurrentWidget(ui.admin_menu);
}


//---------------------------------------------------------------//


//view flight
void s_p_project::show_flights_in_table()
{
    
    ui.table_flights->setRowCount(0);

    
    for (int i = 0; i < (int)flight_list.size(); i++)
    {
        ui.table_flights->insertRow(i);

        
        ui.table_flights->setItem(i, 0, new QTableWidgetItem(QString::number(flight_list[i].flight_code)));

        QTableWidgetItem* rowItem = new QTableWidgetItem(QString::number(flight_list[i].for_planecode));
        rowItem->setFlags(rowItem->flags() & ~Qt::ItemIsEditable);
        ui.table_flights->setItem(i, 1, rowItem);


        ui.table_flights->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(flight_list[i].departure_city)));

        ui.table_flights->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(flight_list[i].arrival_city)));

        QString dateStr = QString::number(flight_list[i].departure_date.day) + " " +QString::fromStdString(flight_list[i].departure_date.month);
        ui.table_flights->setItem(i, 4, new QTableWidgetItem(dateStr));

        QString timeStr = QString::number(flight_list[i].departure_time.hours) + ":" +QString::number(flight_list[i].departure_time.minutes).rightJustified(2, '0');
        ui.table_flights->setItem(i, 5, new QTableWidgetItem(timeStr));                                                 //                             ^
                                                                                                                        //لزوم الحبشتكنات              |
    }
}
void s_p_project::on_btn_view_flights_clicked() {
    show_flights_in_table();
    ui.stackedWidget->setCurrentWidget(ui.view_flights_page);
}
void  s_p_project::on_btn_back_view_flights_clicked() {
    ui.stackedWidget->setCurrentWidget(ui.admin_menu);
}
///search////
void s_p_project::on_btn_search_and_edit_clicked() {
    {
        QString searchText = ui.txt_admin_search_flights->text();

        if (searchText.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter a flight code to search.");
            return;
        }

        int searchCode = searchText.toInt();
        bool found = false;

        for (int i = 0; i < ui.table_flights->rowCount(); i++) {

            if (ui.table_flights->item(i, 0)->text().toInt() == searchCode) {

                ui.table_flights->selectRow(i);
                ui.table_flights->scrollToItem(ui.table_flights->item(i, 0), QAbstractItemView::PositionAtTop);

                found = true;
                break;
            }
        }

        if (!found) {
            QMessageBox::warning(this, "Not Found", "No flight matches that code.");
        }
    }
}
void s_p_project::on_btn_save_view_flights_clicked() 
{
    if (ui.table_flights->rowCount() != (int)flight_list.size()) {
        QMessageBox::critical(this, "Sync Error", "Table and Data are out of sync!");
        return;
    }

    for (int i = 0; i < ui.table_flights->rowCount(); i++) {

        
        flight_list[i].flight_code = ui.table_flights->item(i, 0)->text().toInt();

        flight_list[i].departure_city = ui.table_flights->item(i, 2)->text().toStdString();

        flight_list[i].arrival_city = ui.table_flights->item(i, 3)->text().toStdString();

        QString fullDate = ui.table_flights->item(i, 4)->text();

        QStringList parts = fullDate.split(" ");

        if (parts.size() >= 2) {
            flight_list[i].departure_date.day = parts[0].toInt();
            flight_list[i].departure_date.month = parts[1].toStdString();
        }

        QString fullTime = ui.table_flights->item(i, 5)->text();
        QStringList timeParts = fullTime.split(":");

        if (timeParts.size() >= 2) {
            flight_list[i].departure_time.hours = timeParts[0].toInt();
            flight_list[i].departure_time.minutes = timeParts[1].toInt();
        }

    }

    QMessageBox::information(this, "Success", "All changes have been saved to the system.");


    show_flights_in_table();
}

////the view n edit planes page ////
void s_p_project::show_planes_in_table() {
    ui.table_planes->setRowCount(0);

    for (int i = 0; i < (int)plane_list.size(); i++) {
        ui.table_planes->insertRow(i);

        bool has_bookings = false;
        for (int f = 0; f < (int)flight_list.size(); f++) {
            if (flight_list[f].for_planecode == plane_list[i].plane_code && !flight_list[f].is_empty) {
                has_bookings = true;
                break;
            }
        }

        QTableWidgetItem* codeItem = new QTableWidgetItem(QString::number(plane_list[i].plane_code));
        if (has_bookings) {
            codeItem->setFlags(codeItem->flags() & ~Qt::ItemIsEditable);
            codeItem->setBackground(QColor("#D3D3D3"));
        }
        ui.table_planes->setItem(i, 0, codeItem);

        QComboBox* combo = new QComboBox();
        for (int j = 0; j < 5; j++) {
            combo->addItem(QString::fromStdString(models[j].plane_model));
        }
        combo->setCurrentText(QString::fromStdString(plane_list[i].plane_model));

        combo->setStyleSheet(
            "QComboBox {"
            "   background-color: #4B3621;" // Espresso
            "   color: #EDE0D4;"            // Latte/Cream
            "   border: 1px solid #6F4E37;"
            "}"
            "QComboBox QAbstractItemView {"
            "   background-color: #4B3621;"
            "   color: #EDE0D4;"
            "   selection-background-color: #6F4E37;"
            "}"
        );

        if (has_bookings) {
            combo->setEnabled(false);
            combo->setStyleSheet("background-color: #D3D3D3; color: #555;");
        }
        ui.table_planes->setCellWidget(i, 1, combo);

        QTableWidgetItem* rowItem = new QTableWidgetItem(QString::number(plane_list[i].number_of_rows));
        rowItem->setFlags(rowItem->flags() & ~Qt::ItemIsEditable);
        ui.table_planes->setItem(i, 2, rowItem);

        QTableWidgetItem* colItem = new QTableWidgetItem(QString::number(plane_list[i].number_of_col));
        colItem->setFlags(colItem->flags() & ~Qt::ItemIsEditable);
        ui.table_planes->setItem(i, 3, colItem);
    }
}
void s_p_project::on_btn_view_planes_clicked() {
    show_planes_in_table();
    ui.stackedWidget->setCurrentWidget(ui.view_planes_page);
}


void s_p_project::on_btn_admin_seach_planes_clicked()
{
    QString searchText = ui.txt_admin_search_planes->text();

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a plane code to search.");
        return;
    }

    int searchCode = searchText.toInt();
    bool found = false;

    for (int i = 0; i < ui.table_planes->rowCount(); i++) {

        if (ui.table_planes->item(i, 0)->text().toInt() == searchCode) {

            ui.table_planes->selectRow(i);
            ui.table_planes->scrollToItem(ui.table_planes->item(i, 0), QAbstractItemView::PositionAtTop);

            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Not Found", "No planes matches that code.");
    }
}
/// <summary>
/// saving the changes boiiiiii/////
/// </summary>
void s_p_project::on_btn_save_view_planes_clicked() {

    for (int i = 0; i < (int)plane_list.size(); i++) {
        int new_code = ui.table_planes->item(i, 0)->text().toInt();
        int old_code = plane_list[i].plane_code;

        if (new_code != old_code) {
            for (int f = 0; f < (int)flight_list.size(); f++) {
                if (flight_list[f].for_planecode == old_code) {
                    flight_list[f].for_planecode = new_code;
                }
            }
        }
    }

    plane_list.clear();

    for (int i = 0; i < ui.table_planes->rowCount(); ++i) {
        plane p;

        p.plane_code = ui.table_planes->item(i, 0)->text().toInt();

        QComboBox* combo = qobject_cast<QComboBox*>(ui.table_planes->cellWidget(i, 1));
        p.plane_model = combo->currentText().toStdString();

        for (int j = 0; j < 5; j++) {
            if (p.plane_model == models[j].plane_model) {
                p.number_of_rows = models[j].number_of_row;
                p.number_of_col = models[j].number_of_col;
                break;
            }
        }

        plane_list.push_back(p);
    }

    QMessageBox::information(this, "Saved", "All changes have been applied.");
    show_planes_in_table();
}
    
       


void s_p_project::on_btn_back_view_planes_clicked() {
    ui.stackedWidget->setCurrentWidget(ui.admin_menu);
}

//----------------------------------------------------------------------------------//

void s_p_project::on_btn_login_user_clicked()
{
    QString q_username = ui.txt_login_username_2->text();
    QString q_passport = ui.txt_login_passport->text();


    if (q_username.isEmpty() || q_passport.isEmpty()) {
        QMessageBox::warning(this, "Attention!", "Please enter your Username and Passport number!");
        return; // بيوقف الدالة هنا عشان ميكملش على داتا فاضية
    }

    std::string username = q_username.toStdString();
    std::string passport = q_passport.toStdString();

    user_login_gui(username, passport);

    current_user.username = username;
    current_user.passport_id = passport;

    // 2. //00000000000000000000000000000000000000000000000000000000000000000هنرمي التذكرة الوهمية مباشرة هنا لو الفيكتور فاضي
    if (tickets_list.empty()) {
        ticket t1;
        t1.passenger_name = "Mo Abdelhamed";
        t1.passport_id = "A1234567";
        t1.flight_number = 701;
        t1.departure_city = "CAIRO";
        t1.arrival_city = "PARIS";
        t1.date.day = 15;
        t1.date.month = "march";
        t1.time.hours = 14;
        t1.time.minutes = 30;
        t1.seat_row = 12;
        t1.seat_letter = 'A';

        tickets_list.push_back(t1);
    }

    QMessageBox::information(this, "Success ", "Welcome " + q_username + "!");

    ui.txt_login_username_2->clear();
    ui.txt_login_passport->clear();

    ui.stackedWidget->setCurrentWidget(ui.user_menu_page);

}

void s_p_project::on_btn_back_login_user_clicked()      //  back to admin or user  //
{
    ui.stackedWidget->setCurrentWidget(ui.admin_or_user);
}
//--------------------------------------------------------------------------------------------//  
// user menu
void s_p_project::on_btn_search_flight_clicked()                           
{
    ui.stackedWidget->setCurrentWidget(ui.flight_search_page);
}



void s_p_project::on_btn_back_user_menu_clicked()
{
    ui.stackedWidget->setCurrentWidget(ui.login_user_page);
}

//------------------------------------------------------------------------------//
void s_p_project::on_cmb_search_key_currentTextChanged(const QString& arg1)
{
    // لو اليوزر اختار إنه يبحث بالتاريخ
    if (arg1 == "Date")
    {
        ui.txt_city_search->hide();       // اخفي مربع المدينة
        ui.date_search->show();           // اظهر مربع التاريخ
        ui.lbl_keyword->setText("Enter Date :"); // غير عنوان المربع
    }
    // لو اختار يبحث بالمدينة (Departure City أو Arrival City)
    else
    {
        ui.date_search->hide();           // اخفي مربع التاريخ
        ui.txt_city_search->show();       // اظهر مربع المدينة
        ui.lbl_keyword->setText("Enter City :"); // رجع العنوان لأصله
    }
}
//-----------------------------------------------------------------------------------------//
//search flight 


void s_p_project::on_btn_search_flight_2_clicked()
{
   
    ui.table_flight_search->setRowCount(0);

    // 2. سحب اختيارات اليوزر وتجهيزها للمقارنة
    QString searchBy = ui.cmb_search_key->currentText().trimmed().toLower();
    QString keyword = ui.txt_city_search->text().trimmed().toLower();

    // سحب التاريخ من الـ Date Box وترجمته لكلمة إنجليزي عشان يطابق داتا صحابك
    int search_day = ui.date_search->date().day();
    int month_num = ui.date_search->date().month();
    QStringList english_months = { "", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };
    QString search_month = english_months[month_num];

    int row = 0;

    
    for (int i = 0; i < flight_list.size(); i++)
    {
        bool match = false;

       
        QString current_dep_city = QString::fromStdString(flight_list[i].departure_city).toLower();
        QString current_arr_city = QString::fromStdString(flight_list[i].arrival_city).toLower();
        QString current_month = QString::fromStdString(flight_list[i].departure_date.month).toLower();

        // 4. شروط البحث
        if (searchBy == "departure city" && current_dep_city == keyword)
        {
            match = true;
        }
        else if (searchBy == "arrival city" && current_arr_city == keyword)
        {
            match = true;
        }
        else if (searchBy == "date" && current_month == search_month && flight_list[i].departure_date.day == search_day)
        {
            match = true;
        }

        
        if (match)
        {
            ui.table_flight_search->insertRow(row);

            // ================== DAta Edit ========================//

            // 1. تظبيط الشهر (تكبير أول حرف)
            QString display_month = QString::fromStdString(flight_list[i].departure_date.month);
            if (!display_month.isEmpty())
            {
                display_month[0] = display_month[0].toUpper();
            }
           
            QString fullDate = QString::number(flight_list[i].departure_date.day) + " " + display_month;

            // 2. تظبيط الوقت (AM و PM وصفر الدقايق)
            int h = flight_list[i].departure_time.hours;
            int m = flight_list[i].departure_time.minutes;
           
            QString am_pm = "AM";
            if (h >= 12)
            {
                am_pm = "PM";
                if (h > 12) { h -= 12; }
            }
            if (h == 0)
            {
                h = 12;
            }
           
            QString m_str = QString::number(m);
            
            if (m_str.length() == 1)
            {
                m_str = "0" + m_str;
            }
            QString fullTime = QString::number(h) + ":" + m_str + " " + am_pm;


            // ===================== Show Details ============================//

            ui.table_flight_search->setItem(row, 0, new QTableWidgetItem(QString::number(flight_list[i].flight_code)));
            ui.table_flight_search->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(flight_list[i].departure_city)));
            ui.table_flight_search->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(flight_list[i].arrival_city)));
            ui.table_flight_search->setItem(row, 3, new QTableWidgetItem(fullDate));
            ui.table_flight_search->setItem(row, 4, new QTableWidgetItem(fullTime));

            row++;
        }
    }

    if (row == 0)
    {
        QMessageBox::information(this, "Search Result", "Sorry, No flights found matching your search.");
    }
}

//-------------------------------------------------------------------//

void s_p_project::on_btn_book_seat_clicked() 
{
    
    QString codeStr = ui.txt_enter_flight_code_2->text().trimmed(); 

    
    if (codeStr.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter a Flight Code first.");
        return; // بنوقف التنفيذ هنا
    }

    int enteredCode = codeStr.toInt();
    bool flightFound = false;

    // 3. ندور على كود الرحلة في الفيكتور عشان نتأكد إنه موجود
    for (int i = 0; i < flight_list.size(); i++)
    {
        if (flight_list[i].flight_code == enteredCode)
        {
            flightFound = true;

            
            current_flight_index = i;
            currentFlight = flight_list[i];

            break;
        }
    }

    // 4. لو الكود صح ولقينا الرحلة، ننقله لصفحة الكراسي
    if (flightFound)
    {
        ui.txt_enter_flight_code_2->clear(); 

        
        ui.stackedWidget->setCurrentWidget(ui.book_seat_page);
    }
    else
    {
        
        QMessageBox::warning(this, "Not Found", "Invalid Flight Code. Please enter a valid code from the table.");
    }
}
//-----------------------------------------------------------------// ده بيعمل حاجة اسمها Auto fill لما تدوس على الرحلة هو بيحطها تلقائي في Enter flight code 
void s_p_project::on_table_flight_search_cellClicked(int row, int column)
{
   
    ui.txt_enter_flight_code_2->setText(ui.table_flight_search->item(row, 0)->text());
}

//------------------------
void s_p_project::on_btn_back_search_flight_clicked()      //search flight back
{
    ui.stackedWidget->setCurrentWidget(ui.user_menu_page);
}
//------------------------
void s_p_project::on_btn_back_book_seat_clicked()           //book seat back 
{
    ui.stackedWidget->setCurrentWidget(ui.flight_search_page);
}
//------------------------
void s_p_project::on_btn_back_view_ticket_clicked()        //view ticket back
{
    ui.stackedWidget->setCurrentWidget(ui.user_menu_page);
}

//-------------------------------------------------------------------------------------------------//

void s_p_project::on_btn_view_ticket_clicked()
{
    bool found = false;
    QMessageBox::information(this, "Test", "Number of tickets: " + QString::number(tickets_list.size()));
    // بنلف على ليستة التذاكر
    for (int i = 0; i < tickets_list.size(); i++)
    {
        if (tickets_list[i].passport_id == current_user.passport_id)
        {
            found = true;

            
            QString p_name = QString::fromStdString(tickets_list[i].passenger_name);
            QString dep_city = QString::fromStdString(tickets_list[i].departure_city);
            QString arr_city = QString::fromStdString(tickets_list[i].arrival_city);

            // 2. التاريخ 
            QString month_str = QString::fromStdString(tickets_list[i].date.month).toLower();
            if (!month_str.isEmpty()) {
                month_str[0] = month_str[0].toUpper();
            }
            QString date = QString::number(tickets_list[i].date.day) + " " + month_str;

            // 3. الوقت 
            QString time = QString::asprintf("%02d:%02d", tickets_list[i].time.hours, tickets_list[i].time.minutes);

            // 4. الكرسي 
            QString seat = QString::number(tickets_list[i].seat_row) + QString(QChar(tickets_list[i].seat_letter));

            // 5. رقم الرحلة 
            QString flight_code = QString::number(tickets_list[i].flight_number);

            // البوابة (بما إنها مش في الـ struct حالياً هنديها قيمة ثابتة لحد ما تضيفها)
            QString gate = "B14";

            

            ui.lbl_passenger_ticket->setText(p_name);
            ui.lbl_dep_city->setText(dep_city);
            ui.lbl_arr_city->setText(arr_city);
            ui.lbl_date_ticket->setText(date);
            ui.lbl_flight_code_ticket->setText(flight_code);
            ui.lbl_gate_ticket->setText(gate);
            ui.lbl_time_ticket->setText(time);
            ui.lbl_seat_ticket->setText(seat);

            // دي بتاعة الجزء اللي على جنب في التذكرة (الكعب)1
             ui.lbl_passenger_ticket_2->setText(p_name);
             ui.lbl_date_ticket_2->setText(date);
             ui.lbl_flight_code_ticket_2->setText(flight_code);
             ui.lbl_seat_ticket_2->setText(seat);


            // 3. نظهر صفحة التذكرة
            ui.stackedWidget->setCurrentWidget(ui.view_ticket_page);

            break; 
        }
    }

    // 4. لو مفيش تذكرة
    if (!found)
    {
        QMessageBox::warning(this, "No Ticket", "No ticket found for your passport ID.");
    }
}

