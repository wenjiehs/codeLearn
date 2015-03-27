#pragma once
#include <iostream>
class Singleton
{
public:
	~Singleton(void);
	static Singleton * Instance();
	void show(){std::cout<<"show singleton"<<std::endl;}
protected:
	Singleton(void);
private:
	static Singleton * single;
	
};

