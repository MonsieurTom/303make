#include <iostream>
#include "FileReader.h"
#include "DataExtractor.h"
#include "DataCompiler.h"

int                             main(int ac, char **av)
{
    std::vector<std::string>    wordTab;
    FileReader                  fileReader;
    DataExtractor               dataExtractor;
    DataCompiler                dataCompiler;

    if (ac < 2)
        return 84;
    else if (ac >= 2 && ac <= 3)
    {
        wordTab = fileReader.getWordTabFromFile(av[1]);
        if (wordTab.empty())
            return (84);
        dataExtractor.computeData(wordTab);
        if (ac == 2)
            dataCompiler.compile(dataExtractor.getMap(), dataExtractor.getMap2(), "");
        else
            dataCompiler.compile(dataExtractor.getMap(), dataExtractor.getMap2(), av[2]);
    }
    else
        return (84);
    return 0;
}