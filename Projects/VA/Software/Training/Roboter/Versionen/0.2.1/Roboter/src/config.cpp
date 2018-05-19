#include "config.h"



Config::Config(std::string fileName)
{
    _filename = fileName;
}
Config::~Config()
{

}
bool Config::load()
{
    fileBuffer = std::vector<std::string>();
    file = fopen(_filename.c_str(),"r");
    if(!file)
    {
        qDebug("file: %s konnte nicht geoeffnet oder gefunden werden",_filename.c_str());
        return 1;
    }
    else
    {
        char inBuff[255];
        while(!feof(file))
        {
           for(int a=0; a<255; a++)
           {inBuff[a] = NULL;}
            fgets(inBuff,255,file);
            fileBuffer.push_back(inBuff);
        }
        fclose(file);
    }
    return 0;
}
bool Config::save()
{
    if(fileBuffer.size() == 0)
    {
        qDebug("file: %s no config Data",_filename.c_str());
        return 1;
    }
    file = fopen(_filename.c_str(),"w");
    if(!file)
    {
        qDebug("file: %s konnte nicht geoeffnet oder erstellt werden",_filename.c_str());
        return 1;
    }
    else
    {
        for(int a=0; a<fileBuffer.size(); a++)
        {
            fprintf(file,"%s",fileBuffer[a].c_str());
        }
        fclose(file);
    }
    return 0;
}
std::string Config::parameter(std::string paramName)
{
    if(fileBuffer.size() == 0){return noparam();}
    int row = getParamRow(paramName);
    if(row == -1){return noparam();}
    return getParam(paramName,row);
}
void Config::parameter(std::string paramName, std::string value)
{
    setParam(paramName,value);
}
std::vector<std::string> Config::text()
{
    return fileBuffer;
}
std::string Config::noparam()
{
  return std::string("noParam");
}
int Config::getParamRow(std::string paramName)
{
    int row = -1;
    for(int a=0; a<fileBuffer.size(); a++)
    {
        if(fileBuffer[a].find(paramName) != -1 && fileBuffer[a].find("#") == -1 && fileBuffer[a].find("//") == -1)
        {
            if(row != a && row != -1)
            {
                qDebug("file: %s multiple parameter: %s",_filename.c_str(),paramName.c_str());
                row = -1;
                return row;
            }
            row = a;
        }
    }
    return row;
}
void Config::setParam(std::string paramName,std::string value)
{
    if(getParamRow(paramName) == -1 )
    {
        fileBuffer.push_back(paramName+" "+value+"\n");
    }
    else
    {
        fileBuffer[getParamRow(paramName)] = paramName+" "+value+"\n";
    }
}
std::string Config::getParam(std::string paramName,unsigned int row)
{
    std::string param = noparam();
    if(fileBuffer.size()<= row)
    {
        qDebug("file: %s has no row: %i",_filename.c_str(),row);
        return param;
    }
    if(fileBuffer[row].find(paramName) == -1  && fileBuffer[row].find("#") == -1 && fileBuffer[row].find("//") == -1)
    {
        qDebug("file: %s row: %i param: %s not found",_filename.c_str(),row,paramName.c_str());
        return param;
    }
    param = fileBuffer[row].substr(fileBuffer[row].find(paramName)+paramName.size(),fileBuffer[row].size()-fileBuffer[row].find(paramName)-paramName.size());
    param = param.substr(param.find(" ")+1,param.find("\n")-1);
    return param;
}





