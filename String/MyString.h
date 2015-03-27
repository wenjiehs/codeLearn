#pragma once
#include <string.h>
#include <iostream>
class MyString
{
public:
	MyString();
	MyString(const char * const str);
	MyString(const MyString & rhs);
	size_t lenght();
	const MyString operator+(const MyString & rhs);
	const MyString &operator=(const MyString& rhs);
	bool operator==(const MyString &rhs);
	char operator[](size_t i);
	friend std::ostream& operator<<(std::ostream &output, const MyString & rhs);
	~MyString();
private:
	char *m_pData;
};

