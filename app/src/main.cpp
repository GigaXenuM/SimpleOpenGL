#include "mainwindow.h"
#include "application.h"

int main(void)
{
    MainWindow *mainWindow{ new MainWindow(640, 480, "SimpleOpenGL") };
    Application app(mainWindow);
    return app.run();
}
