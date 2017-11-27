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
	if (strcmp("/v", cmd->commandWord) == 0)
	{
		printf("%s\n", _version);
	}
	if (strcmp("create", cmd->commandWord) == 0)
	{
		if (cmd->countWords == 2) 
		{
			Create(cmd->Words[1]);
			printf("Database [%s] was created\n", cmd->Words[1]);
		}
		else
			printf("Syntax error: The count of arguments does not match! Example CREATE [database name]\n");
	}
	else
	{
		printf("Unknowm command [%s]\n", command);
		delete cmd;
		return -1;
	}
	delete cmd;
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
	thread CommandsThread(&DataBase::ReadCommands, this);
	CommandsThread.join();
	return 0;
}


DataBase::~DataBase()
{
}


#pragma warning( pop ) 