#include "Singleton.h"
Singleton* Singleton::single = NULL;
Singleton::Singleton(void)
{
}


Singleton::~Singleton(void)
{
}
Singleton * Singleton::Instance()
{
	if(single == NULL)
	{
		single = new Singleton();
	}
	return single;
}