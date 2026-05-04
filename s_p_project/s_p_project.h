#include <string>
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_s_p_project.h"




class s_p_project : public QMainWindow
{
    Q_OBJECT

public:
    s_p_project(QWidget *parent = nullptr);
    ~s_p_project();

private:
    Ui::s_p_projectClass ui;
private:
    struct Admin 
    {
        QString username;
        QString password;
    };
    Admin admins[2]; 
private slots:

    void on_btn_enter_clicked();
    void on_btn_choose_user_clicked(); 
    void on_btn_choose_admin_clicked();

    void on_btn_login_submit_clicked();
    void on_btn_back_login_clicked();

    void on_btn_back_admin_clicked();

    //add plane
    void on_btn_addplane_clicked();
    void on_btn_save_plane_clicked();
    void on_btn_back_addplane_clicked();

    //add flight
    void on_btn_add_flight_clicked();
    void on_btn_save_flight_clicked();
    void on_btn_back_flight_clicked();
    

    //view flights
    void on_btn_view_flights_clicked();
    void show_flights_in_table();
    void on_btn_back_view_flights_clicked ();
    void on_btn_search_and_edit_clicked();
    void on_btn_save_view_flights_clicked();

    //view planes////
    void on_btn_view_planes_clicked();
    void show_planes_in_table();
    void on_btn_admin_seach_planes_clicked();
    void on_btn_back_view_planes_clicked();
    void on_btn_save_view_planes_clicked();


 //----------------------------------------------//
    //login user

    void on_btn_login_user_clicked();
    void on_btn_back_login_user_clicked();

   //user menu 
    void on_btn_search_flight_clicked();
    void on_btn_view_ticket_clicked();
    void on_btn_back_user_menu_clicked();

    //search flight 
    void on_btn_search_flight_2_clicked();
    void on_btn_book_seat_clicked();
    void on_btn_back_search_flight_clicked();
    void on_cmb_search_key_currentTextChanged(const QString &arg1);
    void on_table_flight_search_cellClicked(int row, int column);

    //book seat
    void on_btn_back_book_seat_clicked();
    void on_btn_back_view_ticket_clicked();
    void setup_booking_page(int p_code, int f_id);
    void generate_seat_grid(int rows, int cols, std::string letters, int f_id);


    ////
    void on_btn_cancel_ticket_clicked();

    //----------------------------------------------sho new ticket if he has another ticket 
    void on_btn_next_ticket_clicked();
private:
         int current_ticket_index_in_list = -1; 
         void display_ticket_on_screen(int i);  

private slots:
    void handleSeatSelection();
   


};

