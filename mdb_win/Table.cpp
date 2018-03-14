#include "stdafx.h"
//#include <list>

Table::Table(string dataBaseName, string tableName)
{
	_dataBaseName = dataBaseName;
	Name = tableName;
}

int Table::DoSqlCommand(Command * sqlCommand)
{
	if (sqlCommand->Words[0] == "create" && sqlCommand->Words[1] == "table")
	{
		auto c = new Create_Table_Command(sqlCommand->text);
		create();
	}
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
	string path = _directory + _dataBaseName + "\\" + Name + ".dt";
	_dataBaseStream.open(path, ios::in | ios::binary | ios::out | ios::app);
	//char buf[255]; // = "#Table ";
	/*int schemeLength = 0;*/
	//_dataBaseStream.write((char *)&num, sizeof(int));
	//_dataBaseStream << 1 << "test" << 123 << '1' << '3' << endl;
	//_dataBase >> s;
	_dataBaseStream.close();
	return 0;
}
