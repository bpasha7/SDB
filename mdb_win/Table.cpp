#include "Table.h"
#include "DataBase.h"
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
		create(sqlCommand);
	}
	if (sqlCommand->Words[0] == "insert")
	{
		insert(sqlCommand);
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

int Table::create(Command * sqlCommand)
{
	string path = _directory + _dataBaseName + "\\" + Name + ".df";
	_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
	auto sql = new Create_Table_Command(sqlCommand->text);
	
/*	int t = _dataBaseStream.tellp();
	_dataBaseStream.seekp(0);
	t = */
	//start from the beginig
	//_dataBaseStream.tellp();
	
	for (int i = 0; i < sql->CoulumnCount; i++)
	{
		sql->Columns[i]->WriteColumnProperties(&_dataBaseStream);
	}

	_dataBaseStream.close();

	path = _directory + _dataBaseName + "\\" + Name + ".dt";
	_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
	_dataBaseStream.close();
	return 0;
}

int Table::insert(Command * sqlCommand)
{
	
	string path = _directory + _dataBaseName + "\\" + Name + ".dt";
	_dataBaseStream.open(path, ios::in | ios::binary | ios::app);
	auto sql = new Insert_Into(sqlCommand->text);
	for (size_t i = 0; i < sql->Values.size(); i++)
	{
		_dataBaseStream.write(sql->Values[i].c_str(), sql->Values[i].length());
	}
	_dataBaseStream.close();
	return 0;
}
