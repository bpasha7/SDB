#include "Command.h"

class WordDelimitedByCommas : public string
{};

istream& operator>>(std::istream& is, WordDelimitedByCommas& output)
{
	getline(is, output, ',');
	return is;
}

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
	//auto openBracket = commandLine.find_last_of(')');
	//int rt = commandLine.size();
	istringstream iss(
		commandLine.substr(commandLine.find('(') + 1, commandLine.find_last_of(')') - commandLine.find('(') - 1)
	);

	copy(istream_iterator<WordDelimitedByCommas>(iss),
		istream_iterator<WordDelimitedByCommas>(),
		back_inserter(splited));
	//if(splited.size() == 0)


	CoulumnCount = splited.size();
	Columns = new Column * [CoulumnCount];

	for (int i = 0; i < CoulumnCount; i++)
	{
		Columns[i] = new Column(splited[i]);
	}
}

Create_Table_Command::~Create_Table_Command()
{
	//free array of columns
	for (int i = 0; i < CoulumnCount; i++)
	{
		delete Columns[i];
	}
	delete Columns;
}

Select_From::Select_From(string commandLine)
{
	
}

Insert_Into::Insert_Into(string commandLine)
{
	istringstream iss(
		commandLine.substr(commandLine.find('(') + 1, commandLine.find_last_of(')') - commandLine.find('(') - 1)
	);

	copy(istream_iterator<WordDelimitedByCommas>(iss),
		istream_iterator<WordDelimitedByCommas>(),
		back_inserter(Values));
}
