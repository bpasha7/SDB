#pragma once
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

