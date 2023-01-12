#include "fileloader.h"

#include <iostream>
#include <fstream>
#include <sstream>

char *FileLoader::_data{ nullptr };

FileLoader::~FileLoader()
{
    delete _data;
    _data = nullptr;
}

const char *FileLoader::load(const char *path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "ERROR: File " << path << " not opened.";
        return "";
    }

    std::stringstream streamBuffer;
    streamBuffer << file.rdbuf();

    const unsigned long long bufferSize{ streamBuffer.str().size() };
    _data = new char[bufferSize + 1];
    streamBuffer.str().copy(_data, bufferSize);
    _data[bufferSize] = '\0';

    return _data;
}
