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
	string path = _directory + _dataBaseName + "\\" + Name + ".dtt";
	_dataBaseStream.open(path, ios::in | ios::binary | ios::out | ios::app);
	auto sql = new Create_Table_Command(sqlCommand->text);
	
	int t = _dataBaseStream.tellp();
	_dataBaseStream.seekp(0);
	t = _dataBaseStream.tellp();
	for (int i = 0; i < sql->CoulumnCount; i++)
	{
		//sql->Columns[i]->WriteColumnProperties(&_dataBaseStream);
		//_dataBaseStream.write((char *)&sql->Columns[i], sizeof(sql->Columns[i]));
		
		//_dataBaseStream.read((char *)&cl, sizeof(cl));
		Column* cl= new Column(&_dataBaseStream);
		auto n = cl->Name;
		auto s = cl->Size;
	}
	//char buf[255]; // = "#Table ";
	/*int schemeLength = 0;*/
	//_dataBaseStream.write((char *)&num, sizeof(int));
	//_dataBaseStream << 1 << "test" << 123 << '1' << '3' << endl;
	//_dataBase >> s;
	_dataBaseStream.close();
	return 0;
}