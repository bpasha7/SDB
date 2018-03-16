#include "BinaryStream.h"



int BinaryStream::WriteBinaryToSrteam(int value)
{
	string path = _directory + _dataBaseName + "\\" + Name + ".df";
	_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
	_dataBaseStream.write((char *)&value, sizeof(int));
	return 0;
}

BinaryStream::BinaryStream()
{
}


BinaryStream::~BinaryStream()
{
}
