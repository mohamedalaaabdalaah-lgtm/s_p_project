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
    // مجرد ارقام تجربه 
    admins[0].username = "m";
    admins[0].password = "m@123";
    admins[1].username = "mohamedhany";
    admins[1].password = "mohamedhany@123";

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

    ui.stackedWidget->setCurrentIndex(0); // welcome page
    ui.lbl_welcome->setText("Welcome to Egypt Airlines");
    ui.btn_enter->setText("Get Started");
    ui.lbl_a_or_u->setText("Are you an Admin or User ?");
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
    ui.stackedWidget->setCurrentIndex(0); //users return to welcome page until changes
}

void s_p_project::on_btn_choose_admin_clicked()
{
    ui.stackedWidget->setCurrentIndex(2); // go to Login Page
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
        
        ui.stackedWidget->setCurrentIndex(3);//from login to menu
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
    string model = ui.txt_add_model->text().toStdString();
    int code = ui.txt_add_code->text().toInt();

    add_plane_gui(model, code);

    QMessageBox::information(this, "Success", "Plane added successfully!");
    ui.txt_add_model->clear();
    ui.txt_add_code->clear();
    ui.stackedWidget->setCurrentWidget(ui.admin_menu);// Back to Admin Menu   المفروض احنا مش محتاجين السطر ده لان زرار الرجوع هيشتغل مكانه
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
    int depMonth = ui.date_depart->date().month();
    int arrDay = ui.date_arrival->date().day();
    int arrMonth = ui.date_arrival->date().month();

    //سحب الوقت 
    int depHour = ui.time_depart->time().hour();
    int depMinute = ui.time_depart->time().minute();
    int arrHour = ui.time_arrival->time().hour();
    int arrMinute = ui.time_arrival->time().minute();

    bool isSuccess = add_flight_gui(planecode, flightcode, departcity, arrivalcity, departair, arrivalair,
        depDay, depMonth, arrDay, arrMonth,
        depHour, depMinute, arrHour, arrMinute);

    if (isSuccess == true)
    {
        QMessageBox::information(this, "Success","The trip was successfully added");
        ui.txt_plane_code->clear();
        ui.txt_flight_code->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error","The flight code is not available, add the first flight.");
    }
}


void s_p_project::on_btn_back_flight_clicked()       //  back to admin menu  //
{
    ui.stackedWidget->setCurrentWidget(ui.admin_menu);
}


//---------------------------------------------------------------//