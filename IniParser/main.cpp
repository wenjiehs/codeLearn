#include <iostream>
#include "IniParser.h"

using namespace std;

int main()
{
    IniParser ini("E:\\Ollydbg\\ollydbg.ini");

    map<string, string> sec = ini.getSection("CPU");
    //ini.store(string("d:\\1.ini"));

    return 0;
}