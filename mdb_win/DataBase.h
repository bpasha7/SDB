#pragma region Includes
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <windows.h>
#include <direct.h>
#include "Command.h"
#include "Table.h"


#pragma endregion

using namespace std;

const string _directory = "storage\\";
const string _logPath= "logs\\";

#pragma region Defines

#pragma endregion
#pragma warning( push )
#pragma warning( disable : 4996)
class DataBasesBlock
{
public:
	char* Block;
	int Count;
	int Offset;
	DataBasesBlock()
	{
		Count = 0;
		Offset = 0;
	}

};
#pragma once
class DataBase
{
private:
	thread* _commandThread;
	thread* _sqlThread;
	char* _version;
	char* _errorMessage;
	string _currentDB;
	fstream _dataBase;
	ifstream _dataBaseRead;
	int DoCommand(char * command);
	int DoSQL(string sqlCommand);
	int Create(string dbName);
	void SetColor(int ForgC);
	
	int ShowAllDataBases();

	int StartSql();
	int CreateTable(Command * sqlCommand);
public:
	DataBase();
	int ReadCommands();
    int ReadSqlCommands();
	int Start();
	~DataBase();
};



#pragma warning( pop ) 