#include "IniReader.h"

char IniReader::_buf[MAXBUFSIZE];

IniReader::IniReader():_file(NULL)
{
    ;
}

IniReader::IniReader(const char *file):_file(NULL)
{
    _setFilePath(file);
}

void IniReader::setFilePath(const char *file)
{
    _setFilePath(file);
}

const char *IniReader::getFilePath() const
{
    return this->_file;
}

char *IniReader::read(const char *section, const char *key, char *valueBuf, unsigned int size, const char *file, const char *defaultValue = "")
{
    if(file == NULL)
        return NULL;
    GetPrivateProfileString(section, key, defaultValue, valueBuf, size, file);
    return valueBuf;
}

char *IniReader::read(const char *section, const char *key, char *valueBuf, unsigned int size, const char *defaultValue = "")
{
    return read(section, key, valueBuf, size, this->getFilePath(), defaultValue);
}

char *IniReader::read(const char *section, const char *key, const char *defaultValue = "")
{
    return read(section, key, _buf, sizeof(_buf), this->getFilePath(), defaultValue);
}

char *IniReader::_readKeyValuePair(char *buf, char *key, char *value)
{
    unsigned long sz = strlen(buf);
    if(sz == 0)
        return NULL;
    while(*buf != '=')
        *key++ = *buf++;
    *key = '\0';
    ++buf;
    while(*value++ = *buf++);
    return buf;
}

unsigned long IniReader::readSection(const char *section, std::map<std::string, std::string> &keyValuePair, const char *file)
{
    char buf[32767], key[1024], value[1024], *p;
    unsigned long count = 0;
    
    if(file == NULL)
        return 0;
    GetPrivateProfileSection(section, buf, sizeof(buf), file);
    p = buf;
    while(p = _readKeyValuePair(p, key, value))
    {
        keyValuePair[key] = value;
        ++count;
    }
    return count;
}

unsigned long IniReader::readSection(const char *section, std::map<std::string, std::string> &keyValuePair)
{
    return readSection(section, keyValuePair, getFilePath());
}

char *IniReader::readSection(const char *section, char *buf, unsigned int size, const char *file)
{
    if(file == NULL)
        return NULL;
    GetPrivateProfileSection(section, buf, size, file);
    return buf;
}

char *IniReader::readSection(const char *section, char *buf, unsigned int size)
{
    GetPrivateProfileSection(section, buf, size, getFilePath());
    return buf;
}

bool IniReader::write(const char *section, const char *key, const char *value, const char *file)
{
    if(file == NULL)
        return false;
    return WritePrivateProfileString(section, key, value, file);
}

bool IniReader::write(const char *section, const char *key, const char *value)
{
    return write(section, key, value, getFilePath());
}

bool IniReader::writeSection(const char *section, const char *string, const char *file)
{
    if(file == NULL)
        return false;
    return WritePrivateProfileSection(section, string, file);
}

unsigned long IniReader::writeSection(const char *section, std::map<std::string, std::string> &keyValuePair, const char *file)
{
    unsigned long count = 0;
    for(std::map<std::string, std::string>::iterator mit = keyValuePair.begin(); mit != keyValuePair.end(); ++mit)
        if(write(section, mit->first.c_str(), mit->second.c_str(), file))
            ++count;
    return count;
}

bool IniReader::writeSection(const char *section, const char *string)
{
    return writeSection(section, string, getFilePath());
}

unsigned long IniReader::writeSection(const char *section, std::map<std::string, std::string> &keyValuePair)
{
    return writeSection(section, keyValuePair, getFilePath());
}

IniReader::~IniReader()
{
    delete[] _file;
}

void IniReader::_setFilePath(const char *file)
{
    if(_file != NULL)
    {
        delete[] _file;
        _file = NULL;
    }
    
    int len = strlen(file) + 1;
    _file = new char[len];
    strcpy(_file, file);
}


#include <iostream>

using namespace std;

int main()
{
    IniReader ini("./test.ini");
    map<string, string> m;
    cout << ini.readSection("Second", m);
    
    cout << ini.writeSection("Malegebide", m);
}
