#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <QDebug>

class Config
{
    public:
    Config(std::string _fileName);
    ~Config();

    bool load();
    bool save();

    std::string parameter(std::string paramName);
    void parameter(std::string paramName, std::string value);
    std::vector<std::string> text();
    std::string noparam();
    private:
    int getParamRow(std::string paramName);
    void setParam(std::string paramName,std::string value);
    std::string getParam(std::string paramName,unsigned int row);
    FILE *file;
    std::string _filename;
    std::vector<std::string> fileBuffer;
};


#endif // CONFIG_H
