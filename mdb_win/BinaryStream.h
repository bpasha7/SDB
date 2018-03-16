#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class BinaryStream
{
private:
	static fstream _dataBaseStream;
public:
	static int WriteBinaryToSrteam(char value);
	static int WriteBinaryToSrteam(int value);
	static int WriteBinaryToSrteam(string value);

	static int ReadBinaryToSrteam(char * value);
	//int ReadBinaryToSrteam();
	//int ReadBinaryToSrteam();
	BinaryStream();
	~BinaryStream();
};

