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
private slots:
    void on_btn_enter_clicked();
};

