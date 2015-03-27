#pragma once
#include "product.h"
class Factory
{
public:
	Factory(void);
	~Factory(void);
	product* createProduct(char name);
private:

};

