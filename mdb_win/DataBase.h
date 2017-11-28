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
			if (commandString[i] == ' ')
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
	char* _version;
	char* _errorMessage;
	ofstream _dataBase;
	int DoCommand(char * command);
	Command * ToLowevCase(char * command);
	int Create(char* name);
	void SetColor(int ForgC);
public:
	DataBase();
	int ReadCommands();

	int Start();
	~DataBase();
};



#pragma warning( pop ) 