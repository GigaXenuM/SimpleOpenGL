#include "mainwindow.h"
#include "application.h"

#include <iostream>

int main(void)
{
    MainWindow *mainWindow{ new MainWindow(1024, 720, "SimpleOpenGL") };
    Application app(mainWindow);

    return app.run();
}
