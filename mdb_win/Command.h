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
class Create_Table_Command final : SqlCommand
{
public:
	int CoulumnCount;
	Column** Columns;
	Create_Table_Command(string commandLine);
	//~Create_Table_Command();
};

