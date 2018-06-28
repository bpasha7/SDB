#pragma once
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <list>
#include "Record.h"
#include "Column.h"
#include "Error.h"

/*Data set*/
class DataSet
{
private:
	/*Records count of data set*/
	int _count;
	int _columns;
	/*Records of data set*/
	shared_ptr<Record> _records;
	/*Headers of data set records*/
	shared_ptr<string> _headers;
	/*Types of data set records*/
	shared_ptr<char> _types;
public:
	/*Get record by index*/
	Record GetRecord(int index);
	/*Set record by index*/
	bool SetRecord(Record record, int index);
	/*Set record from vector*/
	bool SetRecords(vector<Record> records);
	/*Get count of data set records*/
	int Count();
	/*Get column name by number*/
	string GetColumnName(int columnNumber);
	/*Get column full name(name + type) by number*/
	string GetColumnFullName(int columnNumber);
	/*Get columns count of data set*/
	int Columns();
	DataSet(int count, vector<Column> columns);
	~DataSet();
};

