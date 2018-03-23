#include "Table.h"
#include "DataBase.h"
#include "BinaryStream.h"
//#include <list>

Table::Table(string dataBaseName, string tableName)
{
	_dataBaseName = dataBaseName;
	//cls = make_shared<Column>(12);
	Name = tableName;
	if (isTableExist())
	{

	}
}

int Table::DoSqlCommand(Command * sqlCommand)
{
	if (sqlCommand->Words[0] == "create" && sqlCommand->Words[1] == "table")
	{
		create(sqlCommand);
	}
	if (isTableExist())
	{

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
	std::ifstream ifile(_directory + _dataBaseName + "\\" + Name + ".dt");
	return (bool)ifile;
}

int Table::create(Command * sqlCommand)
{
	string path = _directory + _dataBaseName + "\\" + Name + ".df";
	_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
	auto sql = new Create_Table(sqlCommand->text);
	
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
	
	//string path = _directory + _dataBaseName + "\\" + Name + ".dt";
	//_dataBaseStream.open(path, ios::in | ios::binary | ios::app);
	auto sql = new Insert_Into(sqlCommand->text);
	BinaryStream::Open(_dataBaseName, Name);
	for (size_t i = 0; i < sql->Values.size(); i++)
	{
		BinaryStream::WriteToTable(sql->Values[i]);
		//_dataBaseStream.write(sql->Values[i].c_str(), sql->Values[i].length());
	}
	BinaryStream::Close();
	return 0;
}
