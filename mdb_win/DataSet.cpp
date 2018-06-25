#include "DataSet.h"



Record DataSet::GetRecord(int index)
{
	return *(this->_records.get() + index);
}

bool DataSet::SetRecord(Record record, int index)
{
	record.Values.erase(std::remove(record.Values.begin(), record.Values.end(), "none"), record.Values.end());;
	*(this->_records.get() + index) = record;
	return true;
}

int DataSet::Count()
{
	return _count;
}

string DataSet::GetColumnName(int columnNumber)
{
	return *(this->_headers.get() + columnNumber);
}

string DataSet::GetColumnFullName(int columnNumber)
{
	auto type = *(this->_types.get() + columnNumber);
	auto typeName = "";
	switch (type)
	{
		case '1': typeName = " [int]"; break;
		case '2': typeName = " [byte]"; break;
		case '3': typeName = " [varchar(n)]"; break;
		default: break;
	}
	return *(this->_headers.get() + columnNumber) + typeName;
}

int DataSet::Columns()
{
	// return size of char array, char = 1 byte
	return sizeof(this->_types);
}

DataSet::DataSet(int count, int columnsNumber)
{
	this->_types = shared_ptr<char[]>(new char[columnsNumber](), [](char *p) { delete[] p; });
	this->_headers = shared_ptr<string>(new string[columnsNumber](), [](string *p) { delete[] p; });
	this->_records = shared_ptr<Record>(new Record[count], [](Record *p) { delete[] p; });
}


DataSet::~DataSet()
{
}
