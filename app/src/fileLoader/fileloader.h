#pragma once

#include <string>

class FileLoader
{
public:
    ~FileLoader();

    static const char *load(const char *path);

private:
    static char *_data;
};
