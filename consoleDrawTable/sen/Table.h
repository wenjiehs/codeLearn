#ifndef __H_TABLE__
#define __H_TABLE__

#include <windows.h>
#include <iostream>
#include <deque>
#include <string>

class Table;
class Cell;
class Column;

const int DELIMLEFT = 0;
const int DELIMMID = 1;
const int DELIMRIGHT = 2;

enum Color{
    NONE,
    C_NORMAL = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | 0,
    F_WHITE = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    F_YELLOW = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    F_PURPLE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    F_BLUE = FOREGROUND_BLUE,
    F_GREEN = FOREGROUND_GREEN,
    F_RED = FOREGROUND_RED,
    F_INTENSITY = FOREGROUND_INTENSITY,
    B_BLUE = BACKGROUND_BLUE,
    B_GREEN = BACKGROUND_GREEN,
    B_RED = BACKGROUND_RED,
    B_INTENSITY = BACKGROUND_INTENSITY,
    B_WHITE = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY,
    B_YELLOW = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY,
    B_PURPLE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
};

class Cell
{
public:
    Cell();
    Cell(const std::string &content);
    Cell(const std::string &content, Color color);
    virtual ~Cell();

public:
    virtual void setContent(const std::string &content);
    virtual void setColor(Color color);
    virtual const std::string &getContent() const;
    virtual Color getColor() const;

private:
    std::string _content;
    Color _color;
};


class Column : public Cell
{
public:
    Column();
    Column(const std::string &content);
    Column(const std::string &content, Color color);
    Column(const std::string &content, Color color, int width);

public:
    void setAutoWidth(bool status);
    bool isAutoWidth() const;
    void setWidth(int width);
    void setLimitWidth(int width);
    int getWidth() const;
    Column &operator=(const Column &col);

private:
    int _width;
    int _limitWidth;
    bool _autoWidth;
};

class Table
{
public:
    /* 表格的分隔符 */
    static const char headLine[3][3];
    static const char midLine[3][3];
    static const char wordLine[3][3];
    static const char tailLine[3][3];

    Table();
    Table(int row, int column);
    Table(int row, int column, bool autoWidth);
    ~Table();
    
public:
    /* 创建一个row行, column列的表格 */
    void create(int row, int column);

    /* 创建Column名 */
    template<typename ... Args> void createColumn(const Column &column, Args ... args);
    /* 新增一行 */
    template<typename ... Args> void addNewRow(const Cell &cell, Args ... args);
    
    /* 修改column属性 */
    bool setColumn(const Column &column, int index);
    /* 修改cell属性 */
    bool setCell(const Cell &cell, int row, int column);
    
    /* 返回相关的column */
    Column &getColumn(int index);
    /* 返回指定的cell */
    Cell &getCell(int row, int column);
    
    /* 将表格显示出来 */
    void show(bool reDrawFramework = true, bool eraseBkg = true);
    
    /* 是否显示列名 */
    bool isShowColumnTitle();
    void setShowColumnTitle(bool status);
    
    int getRowSize();
    int getColumnSize();

    /* 删除一行/一列 */
    bool deleteRow(int index);
    bool deleteColumn(int index);
    
private:
    template<typename ... Args> void _createColumn(const Column &column, Args ... args);
    template<typename ... Args> void _addNewRow(const Cell &cell, Args ... args);
    void _createColumn();
    void _addNewRow();
    
private:
    int _rowSz;
    int _columnSz;
    bool _showColumnTitle;
    HANDLE _hCur;
    
protected:
    std::deque<Column> _column;
    std::deque<std::deque<Cell> > _cell;
    
protected:
    void __initTable();
    /* 将文本输出到指定的单元格 */
    void __drawTextToScreen(const std::string &text, int row, int column, Color color);
    /* 绘制表格框架 */
    void __drawFrameworkToScreen();
    /* 绘制表格的线 */
    void __drawLine(const char delims[][3], const char *sep = "─");
    /* 光标移动函数 */
    void __gotoXy(int x, int y);
};


template<typename ... Args> void Table::createColumn(const Column &column, Args ... args)
{
    _createColumn(column, args...);
    while((signed)_column.size() < getColumnSize())
        _column.push_back(Column());
}

template<typename ... Args> void Table::addNewRow(const Cell &cell, Args ... args)
{
    ++_rowSz;
    _cell.resize(_cell.size() + 1);
    _addNewRow(cell, args...);
    while((signed)_cell[_cell.size() - 1].size() < getRowSize())
        _cell[_cell.size() - 1].push_back(Cell());
}

template<typename ... Args> void Table::_createColumn(const Column &column, Args ... args)
{
    if((signed)_column.size() < getColumnSize())
        _column.push_back(column);
    _createColumn(args...);
}

template<typename ... Args> void Table::_addNewRow(const Cell &cell, Args ... args)
{
    int cur;

    if((signed)_cell[_cell.size() - 1].size() < getColumnSize())
    {
        _cell[_cell.size() - 1].push_back(cell);
        cur = _cell[_cell.size() - 1].size() - 1;
        _column[cur].setWidth(_column[cur].getWidth() < (signed)cell.getContent().length() ? cell.getContent().length() : -1);
    }
    _addNewRow(args...);
}

#endif