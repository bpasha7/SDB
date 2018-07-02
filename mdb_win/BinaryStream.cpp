#include "BinaryStream.h"


/*
Description: 
	Writing integer value to binary file of table in database.
Params:
	value - integer value.
Returns:
	integer values
	0	-	OK,
	1	-	FAIL.
*/
int BinaryStream::Write(int value)
{
	try 
	{
		_dataBaseStream.write((char *)&value, sizeof(int));
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}
void BinaryStream::Open(string dataBaseName, string tableName, bool head)
{
	// Close stream if open
	if (_dataBaseStream.is_open())
		_dataBaseStream.close();
	// Generate file path
	string ext = head ? ".df" : ".dt";
	string path = _directory + dataBaseName + "\\" + tableName + ext;
	// Open  binary file stream for writing and reading
	_dataBaseStream.open(path, ios::binary | ios::out | ios::in | ios::ate);
}
void BinaryStream::Create(string dataBaseName, string tableName, bool head)
{
	// Close stream if open
	if (_dataBaseStream.is_open())
		_dataBaseStream.close();
	// Generate file path
	string ext = head ? ".df" : ".dt";
	string path = _directory + dataBaseName + "\\" + tableName + ext;
	// Open  binary file stream for creating new file
	_dataBaseStream.open(path, ios::binary | ios::out | ios::in | ios::app);
}
void BinaryStream::Close()
{
	_dataBaseStream.close();
}
bool BinaryStream::EoF()
{
	return _dataBaseStream.peek() == std::ifstream::traits_type::eof();
}
/*
Description:
	Writing integer value to binary file of table in database.
Params:
	dataBaseName - datebase name,
Returns:
	integer values
	0	-	OK,
	1	-	FAIL.
*/
int BinaryStream::Write(char value)
{
	_dataBaseStream.write((char *)&value, sizeof(char));
	return 0;
}
/*
Description:
	Writing integer value to binary file of table in database.
Params:
	value - integer value.
Returns:
integer values
	0	-	OK,
	1	-	FAIL.
*/
int BinaryStream::Write(string value)
{
	_dataBaseStream.write(value.c_str(), value.length());
	return 0;
}

void BinaryStream::SetPosition(long position)
{
	_dataBaseStream.seekp(position);
}

char BinaryStream::ReadChar()
{
	char val = ' ';
	_dataBaseStream.read((char *)&val, sizeof(char));
	return val;
}

int BinaryStream::ReadInteger()
{
	int val = 0;
	//int t = _dataBaseStream.tellp();
	_dataBaseStream.read((char *)&val, sizeof(int));
	//t = _dataBaseStream.tellp();
	//bool  b = _dataBaseStream.eof();
	return val;
}

char const* BinaryStream::ReadString(int length)
{
	char* val = new char[length + 1];
	_dataBaseStream.read(val, length);
	val[length] = '\0';
	return val;
}

BinaryStream::BinaryStream()
{
}


BinaryStream::~BinaryStream()
{
}
