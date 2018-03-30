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
	static void Create(string dataBaseName, string tableName, bool head);
	static void Open(string dataBaseName, string tableName, bool head);
	static void Close();
	static bool EoF();
	static int Write(char value);
	static int Write(int value);
	static int Write(string value);
	static void SetPosition(long position);

	static char ReadChar();
	static int ReadInteger();
	static char const* ReadString(int length);
	BinaryStream();
	~BinaryStream();
};

