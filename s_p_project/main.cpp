//list of includes in main.cpp
#include "stdafx.h"
#include "s_p_project.h"
#include <QtWidgets/QApplication>
#include <string>
#include <iostream>;
using namespace std;



struct seats
{
	int rows;
	char columns;
};

//plane struct
struct plane
{
    string model;
    int code;
    
};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    s_p_project window;
    window.show();

















    return app.exec();
}
