#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

class DataCompiler
{
public:
    std::map<std::string, std::vector<std::string>> _map;
    std::map<std::string, std::string>              _map2;
    std::vector<std::vector<int>>                   matrix;
    std::vector<std::string>                        RightTab;
    std::vector<std::string>                        LeftTab;
    std::vector<std::string>                        arbre;
    std::vector<std::string>                        loopChecker;
    std::vector<std::string>                        filess;
    bool                                            first;

    DataCompiler() { };
    ~DataCompiler() {};

    void        compile(std::map<std::string, std::vector<std::string>> const &map, std::map<std::string, std::string> map2, std::string file)
    {
        _map = map;
        _map2 = map2;

        if (file == "")
            DrawMadaire();
        else
            DrawDatShit(file);
    }



    void                             initMatrix(unsigned long x, unsigned long y)
    {
        std::vector<int>            vec;

        for (unsigned long i = 0; i < x; i++)
            vec.push_back(0);
        for (unsigned long i = 0; i < y; i++)
            this->matrix.push_back(vec);
    }

    void        drawMaBite(std::string file, std::string aff)
    {
        std::string                     key;
        std::vector<std::string>        dep;

        for (auto map : _map)
        {
            std::string                 newAff;
            key = map.first;
            dep = map.second;

            if (std::find(dep.begin(), dep.end(), file) != dep.end())
            {
                if (std::find(RightTab.begin(), RightTab.end(), key) != RightTab.end()) {
                    newAff = aff;
                    newAff += file ;
                    newAff += " -> ";
                    drawMaBite(key, newAff);
                }
                else
                {
                    newAff = aff;
                    newAff += file;
                    newAff += " -> ";
                    newAff += key;
                    this->arbre.push_back(newAff);
                }
            }
        }
    }

    void        drawDatBite(std::string file, std::string aff)
    {
        std::string                     key;
        std::vector<std::string>        dep;

        for (auto map : _map)
        {
            std::string                 newAff;
            key = map.first;
            dep = map.second;

            if (std::find(dep.begin(), dep.end(), file) != dep.end())
            {
                if (std::find(RightTab.begin(), RightTab.end(), key) != RightTab.end()) {
                    newAff = aff;
                    newAff += _map2[key];
                    newAff += "\n";
                    drawDatBite(key, newAff);
                }
                else
                {
                    newAff = aff;
                    newAff += _map2[key];
                    this->arbre.push_back(newAff);
                }
            }
        }
    }

    void        DrawDatShit(std::string resolver)
    {
        std::string key;
        std::vector<std::string> dependencies;
        std::vector<std::string> files;
        bool found;

        for (auto const &line : _map) {
            found = false;
            key = line.first;
            dependencies = line.second;

            for (unsigned int i = 0; i < files.size(); i++) {
                if (files[i] == key)
                    found = true;
            }
            if (!found)
                files.push_back(key);
            for (auto fileName : dependencies)
            {
                if (std::find(this->RightTab.begin(), this->RightTab.end(), fileName) == this->RightTab.end())
                {
                    if (fileName != "")
                        this->RightTab.push_back(fileName);
                }
                if (!fileName.empty()) {
                    found = false;
                    for (unsigned int i = 0; i < files.size(); i++) {
                        if (files[i] == fileName)
                            found = true;
                    }
                    if (!found)
                        files.push_back(fileName);
                }
            }
        }

        if (std::find(files.begin(), files.end(), resolver) == files.end())
            exit(84);
        
        std::sort(files.begin(), files.end(), [](const std::string &one, const std::string &two) -> bool {
            return (one < two);
        });
        std::sort(this->RightTab.begin(), this->RightTab.end(), [](const std::string &one, const std::string &two) -> bool {
            return (one < two);
        });
        this->drawDatBite(resolver, "");
        for (auto toPrint : this->arbre)
            std::cout << toPrint << std::endl;
        if (this->arbre.empty())
            std::cout << std::endl;
    }

    void        DrawMadaire()
    {
        std::string key;
        std::vector<std::string> dependencies;
        std::vector<std::string> files;
        bool found;

        for (auto const &line : _map) {
            found = false;
            key = line.first;
            dependencies = line.second;
            if (std::find(this->LeftTab.begin(), this->LeftTab.end(), key) == this->LeftTab.end())
                this->LeftTab.push_back(key);

            for (unsigned int i = 0; i < files.size(); i++) {
                if (files[i] == key)
                    found = true;
            }
            if (!found)
                files.push_back(key);
            for (auto fileName : dependencies)
            {
                if (std::find(this->RightTab.begin(), this->RightTab.end(), fileName) == this->RightTab.end())
                {
                    if (fileName != "")
                        this->RightTab.push_back(fileName);
                }
                if (!fileName.empty()) {
                    found = false;
                    for (unsigned int i = 0; i < files.size(); i++) {
                        if (files[i] == fileName)
                            found = true;
                    }
                    if (!found)
                        files.push_back(fileName);
                }
            }
        }

        std::sort(files.begin(), files.end(), [](const std::string &one, const std::string &two) -> bool {
            return (one < two);
        });
        std::sort(this->RightTab.begin(), this->RightTab.end(), [](const std::string &one, const std::string &two) -> bool {
            return (one < two);
        });

        this->initMatrix(files.size(), files.size());
        int     i = 0;
        int     j = 0;

        for (auto const &fileName : files)
        {
            j = 0;
            if (_map.find(fileName) != _map.end())
            {
                for (auto const &fileName2 : files)
                {
                    dependencies = _map[fileName];
                    if (std::find(dependencies.begin(), dependencies.end(), fileName2) != dependencies.end()) {
                        this->matrix[i][j] = 1;
                    }
                    j++;
                }
            }
            i++;
        }

        this->checkMatrix();
        this->filess = files;
        this->checkloops();

        for (unsigned int i = 0; i < files.size(); i++)
        {
            std::cout << '[';
            for (unsigned int j = 0; j < files.size(); j++)
                std::cout << this->matrix[i][j];
            std::cout << ']' << std::endl;
        }
        std::cout << std::endl;

        for (auto fileName : RightTab)
            this->drawMaBite(fileName, "");
        for (auto toPrint : this->arbre)
            std::cout << toPrint << std::endl;
    }

    void                checkMatrix()
    {
        for (unsigned int i = 0; i < this->matrix.size(); i++)
        {
            for (unsigned int j = 0; j < this->matrix[i].size(); j++)
            {
                if (i == j && this->matrix[i][j] == 1)
                {
                    std::cerr << "inclusion de sois-meme." << std::endl;
                    exit(84);
                }
            }
        }
    }

    void                checkloops()
    {
        for (auto fileName : this->filess)
        {
            if (std::find(LeftTab.begin(), LeftTab.end(), fileName) != LeftTab.end())
            {
                for (auto Files : this->_map[fileName])
                {
                    if (std::find(LeftTab.begin(), LeftTab.end(), Files) != LeftTab.end())
                    {
                        for (auto Filess : this->_map[Files])
                        {
                            if (Filess == fileName)
                            {
                                std::cerr << Filess << " depend de " << fileName << "et inversement." << std::endl;
                                exit(84);
                            }
                        }
                    }
                }
            }
        }
    }
};
