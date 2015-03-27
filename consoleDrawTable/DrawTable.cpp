#include "DrawTable.h"
/*
FOREGROUND_BLUE	        ������ɫ����	1
FOREGROUND_GREEN	    ������ɫ����	2
FOREGROUND_RED	        ������ɫ����	4
FOREGROUND_INTENSITY	ǰ��ɫ������ʾ	8
BACKGROUND_BLUE	        ������ɫ����	16
BACKGROUND_GREEN	    ������ɫ����	32
BACKGROUND_RED	        ������ɫ����    64
BACKGROUND_INTENSITY	����ɫ������ʾ	128
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
	//�����ڵ�ָ���Ƿ�Ҫdelete
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
//	//�ݹ���������ģ���Ƶ����ƣ�ÿ��ȡ����һ�������̲������Ĵ�С��
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
	//ע�⣺��Щ�����ķ��ţ�����Ҫ��3���ַ�װ(����/0)
	char lineHead[][3] = {"��", "��", "��"};
	char lineMid1[][3] = {"��", "��", "��"};
	char lineMid2[][3] = {"��", "��", "��"};
	char lineTail[][3] = {"��", "��", "��"};
	cout << lineHead[location]; //����
	for (int i = 0; i < colCount; i++)
	{
		for (int j = 0; j < colWidth/2; j++)
		{
			cout << lineMid1[location];
		}
		if (i < colCount - 1) cout << lineMid2[location];
	}
	cout << lineTail[location] << endl; //��β
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
		cout<<"��λ���Ѿ���ֵ���Ƿ񸲸ǣ�Y/N"<<endl;
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
    char tablines[] = {"���Щ�����ȩ��ة�����"};  
    int i, j;  
  
    colWidth = GetMaxWidth(); //��ȡ���������е������  
    //��ӡ��ͷ��  
    PrintTableLine(0, colCount, colWidth);  
  
    //��ӡ�������  
    for (i = 0; i < rowCount; i++)  
    {  
        if (i > 0) PrintTableLine(1, colCount, colWidth); //��ӡ������  
        cout << "��";  //����  
        for (j = 0; j < colCount; j++)  
        {  
			if(i == 0)//��ӡ����
			{
				cout.width(colWidth);
				if( colNameVec[j])
					cout << colNameVec[j];
				if (j < colCount - 1 ) cout << "��";
				continue;
			}
            cout.width(colWidth);       //���ݰ�ָ�������� 
			if(allValue[(i-1) * colCount + j])
				cout << allValue[(i-1) * colCount+j];  
			else 
				cout << "";
            if (j < colCount - 1 ) cout << "��"; // ��������  
        }  
        cout << "��" << endl;    //��β  
    }  
  
    PrintTableLine(2, colCount, colWidth); //��ӡ��β  
}  
  