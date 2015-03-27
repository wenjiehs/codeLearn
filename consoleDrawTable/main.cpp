#include "DrawTable.h"

int main()
{
	DrawTable table(6, 7);
	table.setColumnName("用户名", "作业名", "状态", "到达时间", "运行时间", "主存", "磁带机", "dddd","ddd","end");
	table.insertRow(1,"111","bbb", "dddssss", "eee","end");
	table.insertRow(2,"sss","bbb", "ddd", "eee","end");
	table.insertRow(3,"sss","bbb", "ddd", "eee","end");
	table.insertRow(4,"sss","bbb", "ddd", "eee","end");
	table.Draw();
	_getch();
	table.addValue(3,1, "你吗的");
	_getch();
	table.delValue(3,1);
	_getch();
	table.clear();
}
