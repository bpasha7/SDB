#include "DataSet.h"



Record DataSet::GetRecord(int index)
{
	if (index >= _count)
		throw new exception("GetRecord: Index is bigger then rows number!");
	return *(this->_records.get() + index);
}

bool DataSet::SetRecord(Record record, int index)
{
	if (index >= _count)
		throw new exception("SetRecord: Index is bigger then rows number!");
	// Remove "none" fields
	record.Values.erase(remove(record.Values.begin(), record.Values.end(), "none"), record.Values.end());
	if(record.Values.size() > this->Columns())
		throw new exception(("SetRecord: " + to_string(index) + " is bigger then rows number!").c_str());
	*(this->_records.get() + index) = record;
	return true;
}

bool DataSet::SetRecords(vector<Record> records)
{
	for (size_t i = 0; i < records.size(); i++)
	{
		this->SetRecord(records[i], i);
	}
	return true;
}

int DataSet::Count()
{
	return _count;
}

string DataSet::GetColumnName(int columnNumber)
{
	if (columnNumber >= this->Columns())
		throw new exception("GetColumnName: Number is bigger then columns number!");
	return *(this->_headers.get() + columnNumber);
}

string DataSet::GetColumnFullName(int columnNumber)
{
	if (columnNumber >= this->Columns())
		throw new exception("GetColumnFullName: Number is bigger then columns number!");
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
	return this->_columns;
}

DataSet::DataSet(int count, vector<Column> columns)
{
	// Find "none" columns 
	vector<int> toDelete;
	for (int i = 0; i < columns.size(); i++)
	{
		if (columns[i].Name == "none")
			toDelete.push_back(i);
	}
	// Delete these columns
	for (int i = toDelete.size() - 1; i >= 0; i--)
	{
		columns.erase(columns.begin() + toDelete[i]);
	}
	this->_columns = columns.size();
	// Create smart pointers
	this->_types = shared_ptr<char>(new char[this->_columns](), [](char *p) { delete[] p; });
	this->_headers = shared_ptr<string>(new string[this->_columns](), [](string *p) { delete[] p; });
	this->_records = shared_ptr<Record>(new Record[count], [](Record *p) { delete[] p; });
	_count = count;
	// Fill columns info
	for (size_t i = 0; i < this->_columns; i++)
	{
		*(this->_types.get() + i) = columns[i].Type;
		*(this->_headers.get() + i) = columns[i].Name;
	}
}

DataSet::~DataSet()
{
}
