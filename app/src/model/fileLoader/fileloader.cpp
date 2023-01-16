#include "fileloader.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string FileLoader::load(const char *path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "ERROR: File " << path << " not opened.";
        return "";
    }

    std::stringstream streamBuffer;
    streamBuffer << file.rdbuf();

    return streamBuffer.str();
}
