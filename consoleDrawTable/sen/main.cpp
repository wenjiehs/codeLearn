#include <iostream>
#include <string>
#include "Table.h"

using namespace std;

int main()
{
    Table *t = new Table(5, 6, false);
    t->setShowColumnTitle(true);
    //t->create(5, 6);
    t->createColumn(
        Column("Hello", B_YELLOW, 4),
        Column("nimi"),
        Column("wocao"),
        Column("wo"),
        Column("wocaonima"),
        Column("test", NONE, 4),
        Column("w", NONE, 3)
    );
    t->setCell(Cell("wocaox"), 0, 5);
    t->show();
    Cell c("test");
    Sleep(1000);
    t->addNewRow(Cell("nimei", F_RED), Cell("wolegequ", F_GREEN));
    t->show();

    Sleep(1000);
    t->deleteRow(2);
    t->show();

    Sleep(1000);
    t->getColumn(1).setLimitWidth(5);
    t->getColumn(1).setAutoWidth(false);
    t->setCell(Cell(string("test")), 2, 2);
    t->show();

    Sleep(1000);
    t->getColumn(0).setAutoWidth(true);
    t->getColumn(5).setAutoWidth(true);
    t->addNewRow(Cell("nimei", F_PURPLE));
    t->show();

    Sleep(1000);
    t->setCell(Cell("nimeiasdsfsafasdasd"), 4, 5);
    t->show();

    Sleep(1000);
    t->deleteColumn(5);
    t->show();

    Sleep(1000);
    t->setCell(Cell("nimageca", F_RED), 2, 3);
    t->setColumn(Column("woca", B_PURPLE), 3);
    t->show();

    Sleep(1000);
    t->getColumn(3).setAutoWidth(false);
    t->show();

    return 0;
}