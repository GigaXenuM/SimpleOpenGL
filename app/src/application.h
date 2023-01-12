#pragma once

#include "iapplication.h"

class MainWindow;

class Application : public IApplication
{
public:
    explicit Application(MainWindow *window);
    ~Application();

    int run() override;

private:
    MainWindow *_window{ nullptr };
};
