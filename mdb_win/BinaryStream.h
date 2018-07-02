#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "DataBase.h"

using namespace std;
static fstream _dataBaseStream;
static class BinaryStream
{
public:
#pragma region File Actions
	static void Create(string dataBaseName, string tableName, bool head);
	static void Open(string dataBaseName, string tableName, bool head);
	static void SetPosition(long position);
	static void Close();
	static bool EoF();
#pragma endregion



#pragma region Writing values to binary file
	/*
	Description:
	Writing char value to binary file
	Params:
	value - char vlaue,
	Returns:
	int
	0	-	OK,
	1	-	FAIL.
	*/
	static int Write(char value);
	/*
	Description:
	Writing integer value to binary file
	Params:
	value - int vlaue,
	Returns:
	int
	0	-	OK,
	1	-	FAIL.
	*/
	static int Write(int value);
	/*
	Description:
	Writing string value to binary file
	Params:
	value - string vlaue,
	Returns:
	int
	0	-	OK,
	1	-	FAIL.
	*/
	static int Write(string value);
#pragma endregion



	static char ReadChar();
	static int ReadInteger();
	static char const* ReadString(int length);
	BinaryStream();
	~BinaryStream();
};

