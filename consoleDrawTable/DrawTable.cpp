#include "DrawTable.h"
/*
FOREGROUND_BLUE	        字体颜色：蓝	1
FOREGROUND_GREEN	    字体颜色：绿	2
FOREGROUND_RED	        字体颜色：红	4
FOREGROUND_INTENSITY	前景色高亮显示	8
BACKGROUND_BLUE	        背景颜色：蓝	16
BACKGROUND_GREEN	    背景颜色：绿	32
BACKGROUND_RED	        背景颜色：红    64
BACKGROUND_INTENSITY	背景色高亮显示	128
*/


DrawTable::DrawTable(int r, int c)
	:row(r), column(c),colWidth(0)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			allValue.push_back(0);
		}
	}
	for(int j = 0; j < c; j++)
	{
		colNameVec.push_back(0);
	}
}
DrawTable::~DrawTable(void)
{
	CloseHandle(hOut);
	//容器内的指针是否要delete
}
void DrawTable::setColumnName(char* colNmae, ...)
{
	char *p;
    va_list ap;
	va_start(ap,colNmae);
	p = colNmae;
	int i = 0;
	while(strcmp(p,"end")!=0 && i < column)
	{
		colNameVec[i++] = p;
		p = va_arg(ap, char *);	
	}
	va_end(ap);
}
//template <typename T, typename ... Args>
//void DrawTable::_write(const T t, Args ... args)
//{
//	colNameStrVec.push_back(t);
//	_write(args...);
//	//递归解决，利用模板推导机制，每次取出第一个，缩短参数包的大小。
//}
void DrawTable::Draw()
{
	system("cls");
	PrintTable(row,column);
	_getch();
	return ;
}
void DrawTable::PrintTableLine(int location, int colCount, int colWidth)
{
	//注意：这些是中文符号，所以要用3个字符装(包括/0)
	char lineHead[][3] = {"┌", "├", "└"};
	char lineMid1[][3] = {"─", "─", "─"};
	char lineMid2[][3] = {"┬", "┼", "┴"};
	char lineTail[][3] = {"┐", "┤", "┘"};
	cout << lineHead[location]; //行首
	for (int i = 0; i < colCount; i++)
	{
		for (int j = 0; j < colWidth/2; j++)
		{
			cout << lineMid1[location];
		}
		if (i < colCount - 1) cout << lineMid2[location];
	}
	cout << lineTail[location] << endl; //行尾
}
int DrawTable::GetMaxWidth()
{
	int width = 0;
	for (int i = 0; i < colNameVec.size(); i++)
	{
		if(colNameVec[i])
			width = width < strlen(colNameVec[i]) ? strlen(colNameVec[i]) : width;	
	}
	for (int i = 0; i < allValue.size(); i++)
	{
		if(allValue[i])
			width = width < strlen(allValue[i]) ? strlen(allValue[i]) : width;	
	}
	return width;
}
void DrawTable::insertRow(int row,char *value, ...)
{
	char *p;
    va_list ap;
	va_start(ap,value);
	p = value;
	int i = 0;
	while(strcmp(p,"end")!=0  && i < column)
	{	
		allValue[(row - 1) * this->column + i] = p;
		p = va_arg(ap, char *);
		i++;
	}
	va_end(ap);
}
void DrawTable::clear(void)
{
	allValue.clear();
	for(int i = 0; i < row; i++)
		for(int j = 0; j < column; j++)
		{
			allValue.push_back(0);
		}
	Draw();
}
void DrawTable::updateValue(int r, int c, char *value)
{
	gotoxy(c + 1, r);
	cout.width(colWidth);
	cout<<value;
	allValue[(r - 1) * this->column + ( c - 1)] = value;
	gotoxy(20,20);
}
void DrawTable::addValue(int r, int c, char *value)
{
	if(allValue[(r - 1) * this->column +( c - 1)])
	{
		gotoxy(20,20);
		cout<<"该位置已经有值，是否覆盖？Y/N"<<endl;
		char flag = getchar();
		if(flag == 'y'||flag == 'Y')
		{
			gotoxy(c + 1, r);
			cout.width(colWidth);
			cout<<value;
			allValue[(r - 1) * this->column + ( c - 1)] = value;
			gotoxy(20,20);
			cout<<"                               ";
		}
		else 
		{
			gotoxy(20,20);
			cout<<"                               ";
		}
	}
}
void DrawTable::delValue(int r, int c)
{
	allValue[(r - 1) * this->column + ( c - 1)] = NULL;
	gotoxy(c + 1, r);
	cout.width(colWidth);
	cout<<" ";
	gotoxy(20,20);
}

void DrawTable::gotoxy(int x, int y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(hOut, pos);
}

void DrawTable::settextcolor(int fore, int background)
{
	SetConsoleTextAttribute(hOut, forecolor[fore]|backcolor[background]);
}
void DrawTable::PrintTable(int rowCount, int colCount)  
{  
    char tablines[] = {"┌┬┐├┼┤└┴┘─│"};  
    int i, j;  
  
    colWidth = GetMaxWidth(); //获取所有数据中的最大宽度  
    //打印表头线  
    PrintTableLine(0, colCount, colWidth);  
  
    //打印表格内容  
    for (i = 0; i < rowCount; i++)  
    {  
        if (i > 0) PrintTableLine(1, colCount, colWidth); //打印表中线  
        cout << "│";  //行首  
        for (j = 0; j < colCount; j++)  
        {  
			if(i == 0)//打印列名
			{
				cout.width(colWidth);
				if( colNameVec[j])
					cout << colNameVec[j];
				if (j < colCount - 1 ) cout << "│";
				continue;
			}
            cout.width(colWidth);       //内容按指定宽度输出 
			if(allValue[(i-1) * colCount + j])
				cout << allValue[(i-1) * colCount+j];  
			else 
				cout << "";
            if (j < colCount - 1 ) cout << "│"; // 表中竖线  
        }  
        cout << "│" << endl;    //行尾  
    }  
  
    PrintTableLine(2, colCount, colWidth); //打印表尾  
}  
  