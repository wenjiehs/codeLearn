#include "Factory.h"


Factory::Factory(void)
{
}


Factory::~Factory(void)
{
}

product* Factory::createProduct(char name)
{
	switch (name)
	{
	case 'A':
		return new productA();
		break;
	case 'B':
		return new productB();
		break;
	case 'C':
		return new productC();
		break;
	default:
		return new productA();
		break;
	}
}