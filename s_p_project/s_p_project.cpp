#include "stdafx.h"
#include "s_p_project.h"
#include <QStackedWidget>

s_p_project::s_p_project(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.lbl_welcome->setText("Welcome to Egypt airlines");
    ui.btn_enter->setText("get started");
}

s_p_project::~s_p_project()
{}
//when get started is pressed
void s_p_project::on_btn_enter_clicked()
{
    ui.lbl_welcome->setText("loading...");
    ui.stackedWidget->setCurrentIndex(1);// From Welcome to Login
}



