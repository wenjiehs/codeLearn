#include "Table.h"

/* Cell */
Cell::Cell():_color(NONE)
{
    ;
}

Cell::Cell(const std::string &content):_content(content), _color(NONE)
{
    ;
}

Cell::Cell(const std::string &content, Color color):_content(content), _color(color)
{
    ;
}

Cell::~Cell()
{
    ;
}

void Cell::setContent(const std::string &content)
{
    _content = content;
}

void Cell::setColor(Color color)
{
    _color = color;
}

const std::string &Cell::getContent() const
{
    return _content;
}

Color Cell::getColor() const
{
    return _color;
}

/* Column */
Column::Column() :_width(0), _limitWidth(0), _autoWidth(true)
{
    ;
}

Column::Column(const std::string &content) : Cell(content), _autoWidth(true)
{
    setWidth(content.length());
    setLimitWidth(content.length());
}

Column::Column(const std::string &content, Color color) : Cell(content, color), _autoWidth(true)
{
    setWidth(content.length());
    setLimitWidth(content.length());
}

Column::Column(const std::string &content, Color color, int width) : Cell(content, color), _autoWidth(false)
{
    setWidth(content.length());
    setLimitWidth(width);
}

void Column::setAutoWidth(bool status)
{
    _autoWidth = status;
}

bool Column::isAutoWidth() const
{
    return _autoWidth;
}

void Column::setLimitWidth(int width)
{
    _limitWidth = (width % 2 == 0) ? width : width + 1;
}

void Column::setWidth(int width)
{
    if(width >= 0)
        _width = (width % 2 == 0) ? width : width + 1;
}

int Column::getWidth() const
{
    if(isAutoWidth())
        return _width;
    return _limitWidth;
}

Column &Column::operator = (const Column &col)
{
    if(_width < col.getWidth())
        _width = col.getWidth();
    _limitWidth = col._limitWidth;
    _autoWidth = col.isAutoWidth();
    return *this;
}

/* Table */
const char Table::headLine[3][3] = { "©°", "©Ð", "©´" };
const char Table::midLine[3][3] = { "©À", "©à", "©È" };
const char Table::wordLine[3][3] = { "©¦", "©¦", "©¦" };
const char Table::tailLine[3][3] = { "©¸", "©Ø", "©¼" };

Table::Table() :_rowSz(0), _columnSz(0), _showColumnTitle(true), _hCur(0)
{
    __initTable();
}

Table::Table(int row, int column) : _rowSz(row), _columnSz(column), _showColumnTitle(true), _hCur(0)
{
    __initTable();
}

Table::Table(int row, int column, bool autoWidth) : _rowSz(row), _columnSz(column), _showColumnTitle(true), _hCur(0)
{
    __initTable();
}

Table::~Table()
{
    CloseHandle(_hCur);
}

void Table::create(int row, int column)
{
    _rowSz = row;
    _columnSz = column;
    _cell.resize(row);
    for(auto &item : _cell)
        item.resize(column);
}

void Table::_createColumn()
{
    ;
}

void Table::_addNewRow()
{
    ;
}

bool Table::setColumn(const Column &column, int index)
{
    if(index < 0 || index >= getColumnSize())
        return false;
    _column[index] = column;
    return true;
}

bool Table::setCell(const Cell &cell, int row, int column)
{
    if(row < 0 || row >= getRowSize() || column < 0 || column >= getColumnSize())
        return false;
    _cell[row][column] = cell;
    if((signed)cell.getContent().length() > _column[column].getWidth())
        _column[column].setWidth(cell.getContent().length());
    return true;
}

Column &Table::getColumn(int index)
{
    return _column[index];
}

Cell &Table::getCell(int row, int column)
{
    return _cell[row][column];
}

void Table::show(bool reDrawFramework, bool eraseBkg)
{
    int tmpI;

    if(eraseBkg)
        system("cls");
    if(reDrawFramework)
    {
        __gotoXy(0, 0);
        __drawFrameworkToScreen();
    }
    else
        __gotoXy(0, 0);
    if(isShowColumnTitle())
    {
        for(int i = 0; i < getColumnSize(); ++i)
            __drawTextToScreen(_column[i].getContent(), 0, i, _column[i].getColor());
    }
    for(int i = 0; i < getRowSize(); ++i)
    {
        tmpI = (isShowColumnTitle() == true ? i + 1 : i);
        for(int j = 0; j < getColumnSize(); ++j)
            __drawTextToScreen(_cell[i][j].getContent(), tmpI, j, _cell[i][j].getColor());
    }
}

int Table::getRowSize()
{
    return _rowSz;
}

int Table::getColumnSize()
{
    return _columnSz;
}

bool Table::isShowColumnTitle()
{
    return _showColumnTitle;
}

void Table::setShowColumnTitle(bool status)
{
    _showColumnTitle = status;
}

bool Table::deleteRow(int index)
{
    if(index < 0 || index >= getRowSize())
        return false;
    _cell.erase(_cell.begin() + index);
    --_rowSz;
    return true;
}

bool Table::deleteColumn(int index)
{
    if(index < 0 || index >= getColumnSize())
        return false;
    _column.erase(_column.begin() + index);
    for(int i = 0; i < getRowSize(); ++i)
        _cell[i].erase(_cell[i].begin() + index);
    --_columnSz;
    return true;
}

void Table::__initTable()
{
    _hCur = GetStdHandle(STD_OUTPUT_HANDLE);
    create(getRowSize(), getColumnSize());
}

void Table::__drawTextToScreen(const std::string &text, int row, int column, Color color)
{
    int x = 2, y = 0;

    if(text.empty())
        return;
    y = row * 2 + 1;

    for(int i = 0; i < column; ++i)
        x += 2 + _column[i].getWidth();
    __gotoXy(x, y);
    if(color != NONE)
        SetConsoleTextAttribute(_hCur, color);
    if((signed)text.length() > _column[column].getWidth())
    {
        if(_column[column].getWidth() >= 2)
        {
            int prefixLen = _column[column].getWidth() - 2;
            for(int i = 0; i < prefixLen; ++i)
                std::cout << text.at(i);
            std::cout << "..";
        }
    }
    else
        std::cout << text;
    if(color != NONE)
        SetConsoleTextAttribute(_hCur, C_NORMAL);
}

void Table::__drawFrameworkToScreen()
{
    int rowToDraw = getRowSize() + (isShowColumnTitle() == true ? 1 : 0);

    __drawLine(headLine);
    for(int i = 0; i < rowToDraw; ++i)
    {
        __drawLine(wordLine, "  ");
        if(i == rowToDraw - 1)
            break;
        __drawLine(midLine);
    }
    __drawLine(tailLine);
}

void Table::__drawLine(const char delims[][3], const char *sep)
{
    std::cout << delims[DELIMLEFT];
    for(int i = 0; i < getColumnSize(); ++i)
    {
        for(int j = 0; j < (signed)_column[i].getWidth(); j += 2)
            std::cout << sep;
        if(i == getColumnSize() - 1)
            break;
        std::cout << delims[DELIMMID];
    }
    std::cout << delims[DELIMRIGHT] << std::endl;
}

void Table::__gotoXy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(_hCur, pos);
}

