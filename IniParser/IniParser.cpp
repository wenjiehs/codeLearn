#include "IniParser.h"


IniParser::IniParser()
{
    ;
}

IniParser::IniParser(std::string filePath)
{
    load(filePath);
}

IniParser::~IniParser()
{
    ;
}

IniParser::OPRetType IniParser::load(std::string &filePath)
{
    _filePath = filePath;
    return _parse(_filePath);
}

void IniParser::setValue(const std::string section, const std::string key, const std::string value, bool isInstant)
{
    _iniMap[section][key] = value;
    if(isInstant)
        store(_filePath);
}

std::string IniParser::getValue(const std::string section, const std::string key, std::string defaultStr)
{
    std::map<std::string, std::map<std::string, std::string> >::iterator it;
    std::map<std::string, std::string>::iterator itSubMap;

    if((it = _iniMap.find(section)) == _iniMap.end())
        return defaultStr;
    if((itSubMap = it->second.find(key)) == it->second.end())
        return defaultStr;
    return itSubMap->second;
}

std::map<std::string, std::string> &IniParser::getSection(const std::string section)
{
    return _iniMap[section];
}

bool IniParser::delKey(const std::string section, const std::string key, bool isInstance)
{
    std::map<std::string, std::map<std::string, std::string> >::iterator it;
    std::map<std::string, std::string>::iterator itSubMap;

    if((it = _iniMap.find(section)) == _iniMap.end())
        return false;
    if((itSubMap = it->second.find(key)) == it->second.end())
        return false;
    it->second.erase(itSubMap);
    if(isInstance)
        store(_filePath);
    return true;
}

bool IniParser::delSection(const std::string section, bool isInstance)
{
    std::map<std::string, std::map<std::string, std::string> >::iterator it;

    if((it = _iniMap.find(section)) == _iniMap.end())
        return false;
    _iniMap.erase(it);
    if(isInstance)
        store(_filePath);
    return true;
}

IniParser::OPRetType IniParser::store(const std::string &newPath)
{
    FILE *output = NULL;

    if(!newPath.empty())
        output = fopen(newPath.c_str(), "w");
    else
        output = fopen(_filePath.c_str(), "w");
    if(output == NULL)
        return WRITEFAIL;

    for(std::map<std::string, std::map<std::string, std::string> >::iterator it = _iniMap.begin(); it != _iniMap.end(); ++it)
    {
        if(it->second.empty())
            continue;
        fprintf(output, "[%s]\n", it->first.c_str());
        for(std::map<std::string, std::string>::iterator subIt = it->second.begin(); subIt != it->second.end(); ++subIt)
            fprintf(output, "%s=%s\n", subIt->first.c_str(), subIt->second.c_str());
    }
    fclose(output);
    return WRITESUCCESS;
}

IniParser::OPRetType IniParser::_parse(const std::string &filePath)
{
    FILE *input = NULL;
    OPRetType retType = READSUCCESS;
    ParseType type;
    std::string curSection = "Default", param1, param2;

    if((input = fopen(_filePath.c_str(), "r")) == NULL)
        return READFAIL;
    while((type = _parseLine(input, param1, param2)) != PARSEENDOFFILE)
    {
        switch(type)
        {
        case PARSESECTION:
            curSection = param1;
            break;
        case PARSEKEYVALUEPAIR:
            _iniMap[curSection][param1] = param2;
            break;
        case PARSEUNKNOW:
            fclose(input);
            return READFAIL;
        }
    }
    fclose(input);
    return retType;
}

std::string IniParser::readValue(const std::string section, const std::string key, const std::string filePath, std::string defaultStr)
{
    FILE *input = NULL;
    std::string curSection, param1, param2;
    ParseType type;

    if((input = fopen(filePath.c_str(), "r")) == NULL)
        return defaultStr;
    while((type = _parseLine(input, param1, param2)) != PARSEENDOFFILE)
    {
        switch(type)
        {
        case PARSESECTION:
            curSection = param1;
            break;
        case PARSEKEYVALUEPAIR:
            if(curSection != section || key != param1)
                break;
            fclose(input);
            return param2;
        }
    }
    fclose(input);
    return defaultStr;
}

std::map<std::string, std::string> IniParser::readSection(const std::string section, const std::string filePath)
{
    std::map<std::string, std::string> tmpMap;
    FILE *input = NULL;
    std::string curSection, param1, param2;
    ParseType type;

    if((input = fopen(filePath.c_str(), "r")) == NULL)
        return tmpMap;
    while((type = _parseLine(input, param1, param2)) != PARSEENDOFFILE)
    {
        switch(type)
        {
        case PARSESECTION:
            curSection = param1;
            break;
        case PARSEKEYVALUEPAIR:
            if(curSection == section)
                tmpMap[param1] = param2;
            break;
        }
    }
    fclose(input);
    return tmpMap;
}

IniParser::ParseType IniParser::_parseLine(FILE *(&file), std::string &param1, std::string &param2)
{
    char buf[INIBUFLEN];
    std::string::size_type size;
    std::string tmp;

    if(fgets(buf, sizeof(buf), file) == NULL)
        return PARSEENDOFFILE;
    tmp.assign(buf);
    tmp.pop_back();
    if(tmp.empty())
        return PARSEEMPTYLINE;
    else if(tmp.front() == ';')
        return PARSECOMMENT;
    else if(tmp.front() == '[' && tmp.back() == ']')
    {
        param1 = tmp.substr(1, tmp.size() - 2);
        return PARSESECTION;
    }
    else if((size = tmp.find('=')) != std::string::npos)
    {
        param1 = tmp.substr(0, size);
        param2 = tmp.substr(size + 1);
        return PARSEKEYVALUEPAIR;
    }
    return PARSEUNKNOW;
}