#pragma once

#include "iapplication.h"

class MainWindow;

class Application : public IApplication
{
public:
    explicit Application();
    ~Application();

    int run() override;

private:
    MainWindow &_window;
};
