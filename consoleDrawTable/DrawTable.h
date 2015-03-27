#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;
using std::string;
using std::vector;
/*
	最多可以做到6(字节) * 9列
	或者 8（字节） * 7列等
	大了会超出一行的大小
*/
class DrawTable
{
public:
	DrawTable(int r, int c);
	~DrawTable(void);

	void setColumnName(char *colName, ...);//最后一个参数必须是"end" -_-!    
	void insertRow(int row, char *value, ...);


	void updateValue(int r, int c, char *value);
	void addValue(int r, int c, char *value);
	void delValue(int r, int c);

	void clear();
	void Draw();
	
protected:
	void gotoxy(int x, int y);
	void settextcolor(int fore, int background);
	void PrintTable(int rowCount, int colCount); 
	int GetMaxWidth();
	void PrintTableLine(int location, int colCount, int colWidth);
private:
	int row;
	int column;
	int colWidth;
	HANDLE hOut;
	vector<char *> colNameVec;
	vector<char *> allValue;
	int forecolor[16];
	int backcolor[16];
};

