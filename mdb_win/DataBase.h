#pragma region Includes
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#pragma endregion

using namespace std;



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
class Command
{
public:
	char* commandWord;
	char* commandString;
	int countWords;
	char** Words;
	void ParseWords()
	{
		char* word = new char[255];
		Words = new char * [countWords];
		int pos = 0;
		int count = 0;
		for (size_t i = 0; i < strlen(commandString); i++)
		{
			if (commandString[i] == ' ' || commandString[i] == ',')
			{
				word[pos] = '\0';
				Words[count] = new char[pos];
				strcpy(Words[count], word);
				count++;
				pos = 0;
			}
			else
			{
				word[pos++] = commandString[i];
			}
		}
		word[pos] = '\0';
		Words[count] = new char[pos];
		strcpy(Words[count], word);
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
	char* _currentDB;
	fstream _dataBase;
	ifstream _dataBaseRead;
	int DoCommand(char * command);
	int DoSQL(char * sqlCommand);
	Command * ToLowevCase(char * command);
	int Create(char* name);
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