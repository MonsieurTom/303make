//
// Created by thosengsu on 26/10/17.
//

#include <fstream>
#include <iostream>
#include "FileReader.h"

std::vector<std::string>        FileReader::getWordTabFromFile(std::string fileName)
{
    std::vector<std::string>    wordTab;
    std::fstream                file;
    std::string                 line;

    file.open(fileName);
    if (!file.is_open())
        return (wordTab);
    else
    {
        while (std::getline(file, line))
            wordTab.push_back(line);
    }
    return (wordTab);
}
