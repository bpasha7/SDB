#pragma once
#include "Command.h"
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
	//Column* _columns;

	int create(Command * sqlCommand);
	bool isTableExist();
};

