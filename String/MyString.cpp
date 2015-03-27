#include "MyString.h"


MyString::MyString()
{
	m_pData = new char[1];
	m_pData[0] = '\0';
}
MyString::MyString(const char * const str)
{
	if (str == NULL)
	{
		m_pData = new char[1];
		m_pData[0] = '\0';
	}
	else
	{
		int len = strlen(str);
		m_pData = new char[len + 1];
		strcpy(m_pData, str);
	}
	
}
MyString::MyString(const MyString &str)
{
	int len = strlen(str.m_pData);
	this->m_pData = new char[len + 1];
	strcpy(m_pData, str.m_pData);
}

const MyString & MyString::operator=(const MyString &rhs)
{
	if (this == &rhs)
		return *this;
	else
	{
		delete[] m_pData;
		m_pData = new char[strlen(rhs.m_pData) + 1];
		strcpy(m_pData, rhs.m_pData);
	}
	return *this;
}
const MyString MyString::operator+(const MyString &rhs)
{
	MyString newString;
	if (rhs.m_pData == NULL)
		newString = *this;
	else if (this->m_pData == NULL)
		newString = rhs;
	else
	{
		int len = strlen(m_pData) + strlen(rhs.m_pData);
		newString.m_pData = new char[len + 1];
		strcpy(newString.m_pData, this->m_pData);
		strcat(newString.m_pData, rhs.m_pData);
	}
	return newString;
}

char MyString::operator[](size_t i)
{
	if (i < lenght())
		return m_pData[i];
	else
		return '\0';
}
size_t MyString::lenght()
{
	return strlen(m_pData);
}
bool MyString::operator==(const MyString &rhs)
{
	return strcmp(m_pData, rhs.m_pData) == 0 ? true : false;
}
std::ostream & operator<<(std::ostream & out, const MyString & rhs)
{
	out<<rhs.m_pData;
	return out;
}
MyString::~MyString()
{
	if (m_pData)
		delete[] m_pData;
	m_pData = NULL;
}
