#pragma once
#include "Command.h"
#include "Record.h"
#include "DataSet.h"
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>

using namespace std;


class Table
{
public:
	string Name;
	Table(string dataBaseName, string tableName);
	int DoSqlCommand(Command * sqlCommand);
	~Table();
private:
	string errMsg;
	fstream _dataBaseStream;
	string _dataBaseName;
	int _tableId;
	int _recordLength;
	vector<Column> _columns;
	//unique_ptr<Column> _columns;
	//Column** _columns;
	vector<Record> _records;
	int columnsCount;
	vector<long> _positions;
	int create(Command * sqlCommand);
	int select(Command * sqlCommand);
	int insert(Command * sqlCommand);
	void showResult(DataSet * ds);
	void showError(int errorNumber, string message);
	bool isTableExist();
	int getScheme();
};

