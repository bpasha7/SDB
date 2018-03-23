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
	static void Open(string dataBaseName, string tableName);
	static void Close();
	static int WriteToTable(char value);
	static int WriteToTable(int value);
	static int WriteToTable(string value);
	/*	int t = _dataBaseStream.tellp();
	_dataBaseStream.seekp(0);
	t = */
	static void SetPosition(int position);

	static char ReadChar();
	static int ReadInteger();
	static string ReadString();
	BinaryStream();
	~BinaryStream();
};

