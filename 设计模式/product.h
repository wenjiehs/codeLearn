#pragma once
#include <iostream>
using std::cout;
using std::endl;
class product
{
public:
	product(void);
	virtual ~product(void);

	virtual void showProduct() = 0;
};

class productA : public product
{
	void showProduct(){cout<<"create product A"<<endl;}
};

class productB : public product
{
	void showProduct(){cout<<"create product B"<<endl;}
};

class productC : public product
{
	void showProduct(){cout<<"create product C"<<endl;}
};