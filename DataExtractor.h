#pragma once

#include <vector>
#include <string>
#include <map>

class DataExtractor
{
private:
    std::map<std::string, std::vector<std::string>>     map;
    std::map<std::string, std::string>                  map2;

    std::vector<std::string>            splitLine(std::string line, char sep);
public:
    DataExtractor() {};
    ~DataExtractor() {};

    void                                   computeData(std::vector<std::string> wordTab);
    std::map<std::string, std::vector<std::string>>     getMap()
    { return (this->map); };
    std::map<std::string, std::string>                  getMap2()
    { return (this->map2); };
};
