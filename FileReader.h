#pragma once

#include <string>
#include <vector>

class FileReader
{
public:
    FileReader() {};
    ~FileReader() {};

public:
    std::vector<std::string>    getWordTabFromFile(std::string fileName);
};
