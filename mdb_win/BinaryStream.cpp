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
int BinaryStream::WriteToTable(int value)
{
	_dataBaseStream.write((char *)&value, sizeof(int));
	return 0;
}
void BinaryStream::Open(string dataBaseName, string tableName)
{
	string path = _directory + dataBaseName + "\\" + tableName + ".dt";
	_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
}
void BinaryStream::Close()
{
	_dataBaseStream.close();
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
int BinaryStream::WriteToTable(char value)
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
int BinaryStream::WriteToTable(string value)
{
	_dataBaseStream.write(value.c_str(), value.length());
	return 0;
}

void BinaryStream::SetPosition(int position)
{
	_dataBaseStream.seekp(position);
}

char BinaryStream::ReadChar()
{
	return 0;
}

BinaryStream::BinaryStream()
{
}


BinaryStream::~BinaryStream()
{
}
