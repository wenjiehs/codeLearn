#ifndef __H_INIREADER__ 
#define __H_INIREADER__

#include <windows.h>
#include <string.h>
#include <string>
#include <map>

const int MAXBUFSIZE = 2048;

/*
        section       :    要设置的小节
        key           :    要设置的键
        value         :    键值
        valueBuf      :    缓冲区
        size          :    缓冲区大小
        file          :    ini文件位置
        defaultValue  :    键值未找到时返回的默认值
        keyValuePair  :    键值对集合            
*/        

class IniReader
{
public:
    IniReader();
    IniReader(const char *file);
    
    /* 设置ini文件的位置 */
    void setFilePath(const char *file);
    
    /* 返回ini文件的位置 */
    const char *getFilePath() const;
    
    /* 静态成员函数, 返回找到的键值 */
    static char *read(const char *section, const char *key, char *valueBuf, unsigned int size, const char *file, const char *defaultValue);
    char *read(const char *section, const char *key, char *valueBuf, unsigned int size, const char *defaultValue);
    
    /* 使用静态缓冲区返回键值, 仅适用于单线程环境 */
    char *read(const char *section, const char *key, const char *defaultValue);
    
    /* 静态成员函数, 返回写入键值是否成功 */
    static bool write(const char *section, const char *key, const char *value, const char *file);
    bool write(const char *section, const char *key, const char *value);
    
    /* 静态成员函数, 返回键值个数 */
    static unsigned long readSection(const char *section, std::map<std::string, std::string> &keyValuePair, const char *file);
    unsigned long readSection(const char *section, std::map<std::string, std::string> &keyValuePair);
    
    /* 
        静态成员函数, 直接调用GetPrivateProfileSection...
        返回的每个键值对中间相隔一个'\0', 末尾有2个'\0' 
        如下:
            key1=value1\0key2=value2\0\0
    */
    static char *readSection(const char *section, char *buf, unsigned int size, const char *file);
    char *readSection(const char *section, char *buf, unsigned int size);
    
    /* 
        静态成员函数, 直接调用WritePrivateProfileSection...
        返回写入成功或者失败
        string格式:key1=value1\0key2=value2\0\0
    */
    static bool writeSection(const char *section, const char *string, const char *file);
    bool writeSection(const char *section, const char *string);
    
    /* 写入键值对集合, 返回写入成功的个数 */
    static unsigned long writeSection(const char *section, std::map<std::string, std::string> &keyValuePair, const char *file);
    unsigned long writeSection(const char *section, std::map<std::string, std::string> &keyValuePair);
    
    ~IniReader();
private:
    char *_file;
    static char _buf[MAXBUFSIZE];
    static char *_readKeyValuePair(char *buf, char *key, char *value);
    void _setFilePath(const char *file);
};

#endif