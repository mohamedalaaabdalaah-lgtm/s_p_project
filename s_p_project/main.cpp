//list of includes in main.cpp
#include "stdafx.h"
#include "s_p_project.h"
#include <QtWidgets/QApplication>
#include <string>
#include <vector>
#include <iostream>
#include "data.h"
#include "logic.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;



int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    s_p_project window;
    window.show();

	srand(time(0));// initialize random values.

    LoadAllData();

    start();

    SaveAllData();

    return app.exec();
}
