#ifndef __H_INIPARSER__
#define __H_INIPARSER__

#include <map>
#include <string>
#include <cstdio>

#ifndef INIBUFLEN
#define INIBUFLEN 2048
#endif

class IniParser
{
public:
    enum OPRetType {READSUCCESS, READFAIL, WRITESUCCESS, WRITEFAIL};
    IniParser();
    IniParser(std::string filePath);
    ~IniParser();

public:
    OPRetType load(std::string &filePath);
    OPRetType store(const std::string &newPath);

    void setValue(const std::string section, const std::string key, const std::string value, bool isInstant = false);
    std::string getValue(const std::string section, const std::string key, std::string defaultStr = "");
    std::map<std::string, std::string> &getSection(const std::string section);

    bool delKey(const std::string section, const std::string key, bool isInstance = false);
    bool delSection(const std::string section, bool isInstance = false);

public:
    static std::string readValue(const std::string section, const std::string key, const std::string filePath, std::string defaultStr = "");
    static std::map<std::string, std::string> readSection(const std::string section, const std::string filePath);

private:
    enum ParseType { PARSESECTION, PARSEKEYVALUEPAIR, PARSECOMMENT, PARSEEMPTYLINE, PARSEENDOFFILE, PARSEUNKNOW };
    IniParser::OPRetType _parse(const std::string &filePath);
    static ParseType _parseLine(FILE *(&file), std::string &param1, std::string &param2);

private:
    std::string _filePath;
    std::map<std::string, std::map<std::string, std::string> > _iniMap;
};

#endif

