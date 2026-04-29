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
    struct Admin {
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


 






};

