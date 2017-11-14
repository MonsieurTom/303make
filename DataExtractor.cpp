//
// Created by thosengsu on 26/10/17.
//

#include <sstream>
#include "DataExtractor.h"

void                           DataExtractor::computeData(std::vector<std::string> wordTab)
{
    std::string                                                 keyMap;
    bool                                                        keyMapUsed = false;
    std::map<std::string, std::vector<std::string>>             map;
    std::map<std::string, std::string>                          map2;
    unsigned long                                               idx;

    for (std::string line : wordTab)
    {
        if ((idx = line.find(':')) != std::string::npos)
        {
            if (idx == 0)
                exit(84);

            keyMap = line.substr(0, idx);
            keyMapUsed = true;
            line = line.substr(idx + 1);
            map[keyMap] = splitLine(line, ' ');
        }
        else if (!line.empty())
        {
            if (keyMapUsed && !keyMap.empty())
            {
                map2[keyMap] = line;
                keyMap = "";
                keyMapUsed = false;
            }
            else
                exit (84);
        }
    }
    this->map = map;
    this->map2 = map2;
}

std::vector<std::string>        DataExtractor::splitLine(std::string line, char sep)
{
    std::stringstream           ss(line);
    std::string                 newLine;
    std::vector<std::string>    vec;

    while (std::getline(ss, newLine, sep))
        vec.push_back(newLine);
    return vec;
}