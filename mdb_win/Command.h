#include <sstream>
//#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;
#pragma once
/*
Класс обработки комадной строки
*/
class Command
{
	public:
		vector<string> Words;
		Command(string commandLine);
		~Command();
};

