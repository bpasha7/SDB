#include <sstream>
//#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
//#include "stdafx.h"
#include "Column.h"

using namespace std;
#pragma once
/*
Класс обработки комадной строки
*/
class Command
{
public:
	string text;
		vector<string> Words;
		Command(string commandLine);
		~Command();
};
class SqlCommand {

protected:
	string trim(const std::string& str,
		const std::string& whitespace = " \t");
};
class Create_Table final : SqlCommand
{
public:
	int CoulumnCount;
	Column** Columns;
	Create_Table(string commandLine);
	~Create_Table();
};

class Select_From final : SqlCommand
{
public:
	string Table;
	bool AllColumns;
	vector<string> Filter;
	string OrderBy;
	vector<string> ColumnsName;
	Select_From(Command * command);
	//~Select_From();
};

class Insert_Into final : SqlCommand
{
public:
	vector<string> Values;
	Insert_Into(string commandLine);
	void padTo(string &str, const size_t num, const char paddingChar = 0);
	//~Select_From();
};




