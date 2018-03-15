#pragma once
#include <string>
#include <sstream>

using namespace std;

static class DataBaseException
{
private:
	//fstream _logStream;
public:
	int ErrorCode;
	string Message;
	DataBaseException();
	~DataBaseException();
};

