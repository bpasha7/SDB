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
	//int CoulumnCount;
	vector<string> Values;
	Select_From(string commandLine);
	//~Select_From();
};

class Insert_Into final : SqlCommand
{
public:
	//int CoulumnCount;
	vector<string> Values;
	Insert_Into(string commandLine);
	//~Select_From();
};



