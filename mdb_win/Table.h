#pragma once
class Table
{
public:
	string Name;
	Table(string dataBaseName, string tableName);
	int DoSqlCommand(Command *sqlCommand);
	~Table();
private:

	fstream _dataBaseStream;
	string _dataBaseName;
	int _tableId;
	Column *_columns;
	int create();
	bool isTableExist();
};

