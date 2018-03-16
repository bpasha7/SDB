#include "Column.h"
#pragma warning(push)
#pragma warning(disable : 4996)
Column::Column(string arguments)
{
	vector<string> splited;

	istringstream iss(arguments);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(splited));

	if (splited.size() > 1)
	{
		Name = splited[0];
		//strcpy(Name, splited[0].c_str());
		//strncpy_s<splited[0].size()>(Name, splited[0].c_str(), splited[0].size());
		//if(splited[0].size() < 25)
			//strcpy_s(Name, splited[0].c_str());
		//Name = const_cast<char*>(splited[0].c_str());
		parseType(splited[1]);
	}

	/*for (int i = 0; i < splited.size(); i++)
	{
		auto column = new Column(splited[i]);
	}*/
}
//
Column::Column(fstream *stream)
{
	int size = 0;
	//
	stream->read((char *)&size, sizeof(int));
	char* buf = new char[size];
	stream->read(buf, size);
	Name = buf;
	Name = Name.substr(0, size);
	//
	stream->read((char *)&Type, sizeof(char));
}

//Write properties  of columns into scheme file
int Column::WriteColumnProperties(fstream *stream)
{
	//Write length of column name
	writeBinaryToSrteam(stream, (int)Name.length());
	//Write column name
	writeBinaryToSrteam(stream, Name);
	//Write type of column
	writeBinaryToSrteam(stream, Type);
	return 0;
}

//int Column::ReadColumnProperties(fstream stream)
//{
//	
//	return 0;
//}


Column::~Column()
{
}

int Column::parseType(string type)
{
	string newType = type;
	int newSize = 0;
	//Getting length of new column if it dynamic
	if (type.find('(') != string::npos)
	{
		//get type
		newType = type.substr(
			0,
			type.find_first_of('(')
		);
		//get length
		newSize = stoi(type.substr(
			type.find_first_of('(') + 1,
			type.find_last_of(')') - type.find_first_of('(') - 1
		));
	}
	//set type

	if (newType == "int")
	{
		Type = '1';
		Size = sizeof(int);
		return 0;
	}
	if (newType == "bit")
	{
		Type = '2';
		Size = sizeof(bool);
		return 0;
	}
	if (newType == "varchar")
	{
		Type = '3';
		Size = newSize;
		return 0;
	}	
	return -1;
}
//Write into binary stream int value
int Column::writeBinaryToSrteam(fstream * stream, int value)
{
	stream->write((char *)&value, sizeof(int));
	return 0;
}
//Write into binary stream string value
int Column::writeBinaryToSrteam(fstream * stream, string value)
{
	stream->write(value.c_str(), (int)value.length());
	return 0;
}
//Write into binary stream char value
int Column::writeBinaryToSrteam(fstream * stream, char value)
{
	stream->write((char *)&value, sizeof(char));
	return 0;
}
