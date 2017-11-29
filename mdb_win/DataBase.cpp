#include "stdafx.h"
#include "DataBase.h"
#pragma warning( push )
#pragma warning( disable : 4996)
/*
	Функция Формирование из команды структуру "Command"
*/
Command * DataBase::ToLowevCase(char * command)
{
	bool isCommand = true;
	int last = 0;
	Command* cmd = new Command;
	size_t length = strlen(command);
	cmd->commandString = new char[length];
	cmd->countWords = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (isCommand)
		{
			if (command[i] == ' ')
			{
				isCommand = false;
				cmd->commandString[i] = command[i];
				last = i;
				cmd->countWords++;
				continue;
			}
			if (command[i] <= 'Z' && command[i] >= 'A')
				cmd->commandString[i] = command[i] - ('Z' - 'z');
			else
				cmd->commandString[i] = command[i];
		}
		else
		{
			if (command[i] == ' ')
				cmd->countWords++;
			cmd->commandString[i] = command[i];
		}
	}
	cmd->countWords++;
	cmd->commandString[length - 1] = '\0';
	cmd->commandWord = new char[last];
	memcpy(cmd->commandWord, cmd->commandString, last);
	cmd->commandWord[last] = '\0';
	cmd->ParseWords();
	return cmd;
}
/*
	Обработка команд СУБД
*/
int DataBase::DoCommand(char * command)
{
    Command* cmd = ToLowevCase(command);
	if (strcmp("/v", cmd->Words[0]) == 0)
	{
		SetColor(10);
		printf("%s\n", _version);
		SetColor(7);
		return 1;
	}
	if (cmd->commandString[0] == '#')
	{
		_currentDB = new char[strlen(cmd->commandString)];
		strcpy(_currentDB, cmd->commandString);
		StartSql();
	}
	if (strcmp("create", cmd->commandWord) == 0)
	{
		if (cmd->countWords == 2) 
		{
			SetColor(10);
			Create(cmd->Words[1]);
			printf("Database [%s] was created\n", cmd->Words[1]);
			SetColor(7);
			return 1;
		}
		else
			printf("Syntax error: The count of arguments does not match! Example CREATE [database name]\n");
		return 0;
	}
	else
	{
		SetColor(12);
		command[strlen(command) - 1] = '\0';
		printf("Unknowm command [%s]\n", command);
		SetColor(7);

		delete cmd;
		return -1;
	}
	delete cmd, command;
	return 0;
}

int DataBase::DoSQL(char * sqlCommand)
{
	Command* cmd = ToLowevCase(sqlCommand);
	//
	if (strcmp(cmd->Words[0], "create") == 0 && strcmp(cmd->Words[1], "table") == 0)
	{
		CreateTable(Command * sqlCommand);
	}
	return 0;
}

DataBase::DataBase()
{
	_version = "edb for Windows v0.0.1";
}
/*
	Чтение команд из консоли
*/
int DataBase::ReadCommands()
{
	char command[255];

	while (true)
	{
		printf("SDB: ");
		fgets(command, 255, stdin);
		//command[strlen(command) - 1] = '\0';
		DoCommand(command);
	}
	return 0;
}
/*
	Создание БД
*/
int DataBase::Create(char * name)
{
	_dataBase.open("data.edb", ios::in | ios::binary | ios::app);
	char buf[255];// = "#Table ";
	int schemeLength = 0;
	sprintf(buf, "#DATABASE %s\n", name);
	//strcat(buf, name);
	_dataBase.write(buf, strlen(buf));
	_dataBase.close();
		return 0;
}

int DataBase::Start()
{
	_commandThread = new thread(&DataBase::ReadCommands, this);
	_commandThread->join();
	//CommandsThread.join();
	return 0;
}


DataBase::~DataBase()
{
}
#include <windows.h>
#include <dos.h>
void DataBase::SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

int DataBase::StartSql()
{
	_commandThread->detach();
	delete _commandThread;
	
	_commandThread = new thread(&DataBase::ReadSqlCommands, this);
	_commandThread->join();
	return 0;
}

int DataBase::ReadSqlCommands()
{
	char command[255];

	while (true)
	{
		printf("%s: ", _currentDB);
		fgets(command, 255, stdin);
		//command[strlen(command) - 1] = '\0';
		DoSQL(command);
	}
	return 0;
}



int DataBase::CreateTable(Command * sqlCommand)
{
	_dataBase.open("data.edb", ios::in | ios::binary | ios::app);
	char buf[255];// = "#Table ";
	int schemeLength = 0;
	sprintf(buf, "#Table %s\n", sqlCommand->Words[2]);
	//strcat(buf, name);
	_dataBase.write(buf, strlen(buf));
	_dataBase.close();
	return 0;
	return 0;
}


#pragma warning( pop ) 