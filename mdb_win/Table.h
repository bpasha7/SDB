#pragma once
#include "Command.h"
#include "Record.h"
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class Table
{
public:
	string Name;
	Table(string dataBaseName, string tableName);
	int DoSqlCommand(Command * sqlCommand);
	~Table();
private:
	
	fstream _dataBaseStream;
	string _dataBaseName;
	int _tableId;
	//shared_ptr<Column> cls;
	Column** _columns;
	vector<Record> _records;
	int columnsCount;

	int create(Command * sqlCommand);
	int select(Command * sqlCommand);
	int insert(Command * sqlCommand);
	void showResult();
	bool isTableExist();
	int getScheme();
};

