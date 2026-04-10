#include "stdafx.h"
#include "s_p_project.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    s_p_project window;
    window.show();
    return app.exec();
}
