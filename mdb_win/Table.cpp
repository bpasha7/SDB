#include "stdafx.h"
#include "Table.h"
#include "Column.h"
//#include <list>

Table::Table(string dataBaseName, string tableName)
{
	_dataBaseName = dataBaseName;
	Name = tableName;
}

int Table::DoSqlCommand(Command * sqlCommand)
{
	
	return 0;
}

Table::~Table()
{
}

bool Table::isTableExist()
{
	return false;
}

int Table::create()
{
	_dataBaseStream.open(_directory + Name + ".db", ios::in | ios::binary | ios::out);
	//char buf[255]; // = "#Table ";
	/*int schemeLength = 0;
	_dataBaseStream >> schemeLength;*/
	//_dataBase >> s;
	_dataBaseStream.close();
	return 0;
}
