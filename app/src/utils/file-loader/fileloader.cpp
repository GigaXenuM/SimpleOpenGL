#include "fileloader.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string Utils::FileLoader::load(const char *path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "ERROR: File " << path << " not opened.";
        return "";
    }

    std::stringstream streamBuffer;
    streamBuffer << file.rdbuf();
    file.close();

    return streamBuffer.str();
}
