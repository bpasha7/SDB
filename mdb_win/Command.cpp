#include "stdafx.h"
#include "Command.h"


Command::Command(string commandLine)
{
	text = commandLine;
	//auto x = commandLine.find('(');
	//auto l = commandLine.find_last_of(')');
	//commandLine.substr(commandLine.find('('), commandLine.find_last_of(')'));

	istringstream iss(commandLine);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(Words));
}


Command::~Command()
{
}

Create_Table_Command::Create_Table_Command(string commandLine)
{
	//Columns
	vector<string> splited;

	istringstream iss(
		commandLine.substr(commandLine.find('('), commandLine.find_last_of(')'))
	);

	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(splited));

	//if(splited.size() == 0)
	Columns = new Column * [splited.size()];

	for (int i = 0; i < splited.size(); i++)
	{
		Columns[i] = new Column(splited[i]);
	}
}




class WordDelimitedByCommas : public string
{};

istream& operator>>(std::istream& is, WordDelimitedByCommas& output)
{
	getline(is, output, ',');
	return is;
}
