#pragma once
#include <vector>
#include <iostream>
#include <string>
class Product 
{
public:
	void add(std::string str){vec.push_back(str);}
	void show()
	{
		for(std::string &str: vec)
		{
			std::cout<<str<<std::endl;
		}
	}
private:
	std::vector<std::string> vec;
};

class Builder
{
public:
	virtual void buildA() = 0;
	virtual void buildB() = 0;
	virtual void buildC() = 0;
	Product * getProduct(){return pro;}
	Builder(void){pro = new Product();}
	~Builder(void){}//if(pro) delete pro;};
protected:
	Product *pro;
};


class BuilderBig : public Builder
{
public:
	virtual void buildA(){pro->add("AAA");}
	virtual void buildB(){pro->add("BBB");}
	virtual void buildC(){pro->add("CCC");}
	BuilderBig(void){};
	~BuilderBig(void){};

};
class BuilderSmall : public Builder
{
public:
	virtual void buildA(){pro->add("aaa");}
	virtual void buildB(){pro->add("bbb");}
	virtual void buildC(){pro->add("ccc");}
	BuilderSmall(void){};
	~BuilderSmall(void){};

};

class Director
{
public:
	Director(Builder * builder){this->builder = builder;}
	Product* conStruct()
	{
		builder->buildA();
		builder->buildB();
		builder->buildC();
		return builder->getProduct();
	}
	~Director(){}
private:
	Builder *builder;
};