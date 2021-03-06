#include "DataBase.h"
#pragma warning(push)
#pragma warning(disable : 4996)
/*
	Функция Формирование из команды структуру "Command"
*/
/*Command * DataBase::ToLowevCase(char * command)
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
}*/
/*
	Обработка команд СУБД
*/

int DataBase::DoCommand(char * command)
{
	Command *cmd = new Command(command);
	if (cmd->Words[0].compare("/v") == 0)
	{
		SetColor(10);
		printf("%s\n", _version);
		SetColor(7);
		return 1;
	}
	if (cmd->Words[0].compare("#") == 0)
	{
		/*_currentDB = new char[strlen(cmd->commandString)];
		strcpy(_currentDB, cmd->commandString);*/
		_currentDB = cmd->Words[1];
		StartSql();
	}
	if (cmd->Words[0].compare("create") == 0)
	{
		if (cmd->Words.size() == 2)
		{
			SetColor(10);
			Create(cmd->Words[1]);
			cout << "Database was created\n";
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


int DataBase::DoSQL(string sqlCommand)
{
	if (sqlCommand == "#")
		return -1;
	Command *cmd = new Command(sqlCommand);
	Table* table = nullptr;
	//
	if (cmd->Words[0].compare("create") == 0 && cmd->Words[1].compare("table") == 0)
	{
		table = new Table(_currentDB, cmd->Words[2]);
	}
	if (cmd->Words[0].compare("insert") == 0 && cmd->Words[1].compare("into") == 0)
	{
		table = new Table(_currentDB, cmd->Words[2]);
	}	
	if (cmd->Words[0] == "select")
	{
		table = new Table(_currentDB, "");
	}
	table->DoSqlCommand(cmd);
	
	//delete table;
	return 0;
}

DataBase::DataBase()
{
	_version = "edb for Windows v0.0.1";
	_dataBaseRead.open("storage\\data.edb", ios::in | ios::binary);
	if (_dataBaseRead.peek() == ofstream::traits_type::eof())
	{
		_dataBaseRead.close();
		_dataBase.open("storage\\data.edb", ios::in | ios::binary | ios::app); //
		int num = 0;
		//tag
		//_dataBase.write("#DATABASES", 10);
		//bases count
		_dataBase.write((char *)&num, sizeof(int));
		//position for write
		num = sizeof(int);
		_dataBase.write((char *)&num, sizeof(int));
		_dataBase.close();
	}
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
int DataBase::Create(string dbName)
{
	_dataBase.open("storage\\data.edb", ios::out | ios::in | ios::binary);
	int t = _dataBase.tellp();

	_dataBase.seekp(0);
	t = _dataBase.tellp();

	DataBasesBlock *bases = new DataBasesBlock();
	_dataBase.read((char *)&bases->Count, sizeof(int));
	_dataBase.read((char *)&bases->Offset, sizeof(int));
	//_dataBaseRead.close();
	//_dataBase.open("data.edb", ios::binary | ios::out);
	_dataBase.seekp(bases->Offset);
	//char buf[255];// = "#Table ";
	//int schemeLength = 0;
	//sprintf(buf, "#DATABASE %s", name);
	//strcat(buf, name);
	int length = dbName.length();
	_dataBase.write((char *)&length, sizeof(int));
	_dataBase.write(dbName.c_str(), dbName.length());
	length += sizeof(int);
	bases->Count++;
	bases->Offset += length;
	_dataBase.seekp(0);
	_dataBase.write((char *)&bases->Count, sizeof(int));
	_dataBase.write((char *)&bases->Offset, sizeof(int));
	_dataBase.close();
	//char buf[255];// = "#Table ";
	//sprintf(buf, "%s.db", name);
	mkdir(("storage\\" + dbName).c_str());
	/*_dataBase.open("storage\\" + dbName + ".db", ios::in | ios::binary | ios::app);
	_dataBase.close();*/
	return 0;
}

int DataBase::Start()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
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

int DataBase::ShowAllDataBases()
{
	return 0;
}

int DataBase::StartSql()
{
	_commandThread->detach();
	delete _commandThread;

	_commandThread = new thread(&DataBase::ReadSqlCommands, this);
	_commandThread->join();
	_commandThread = new thread(&DataBase::ReadCommands, this);
	_commandThread->join();
	return 0;
}

int DataBase::ReadSqlCommands()
{
	//char command[255];
	string command = "";
	while (true)
	{
		//printf("%s: ", _currentDB);
		cout << _currentDB << ": ";
		//fgets(command, 255, stdin);
		getline(cin, command);
		//command[strlen(command) - 1] = '\0';
		if (DoSQL(command) == -1)
			break;
	}
	return 0;
}

#pragma warning(pop)