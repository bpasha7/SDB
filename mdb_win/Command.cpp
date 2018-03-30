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

string SqlCommand::trim(const std::string & str, const std::string & whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

Create_Table::Create_Table(string commandLine)
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

Create_Table::~Create_Table()
{
	//free array of columns
	for (int i = 0; i < CoulumnCount; i++)
	{
		delete Columns[i];
	}
	delete Columns;
}

Select_From::Select_From(Command * command)
{
	if (command->Words[1] == "*")
		AllColumns = true;
	else
	{

	}
	//std::vector<string>::iterator it;
	auto pos = find(command->Words.begin(), command->Words.end(), "from") - command->Words.begin();
	//if word from not exist
	if (pos >= command->Words.size()) {
		//old_name_ not found
	}
	//not contain table name
	if ((int)pos + 1 > command->Words.size())
	{

	}
	Table = command->Words[pos + 1];
}

Insert_Into::Insert_Into(string commandLine)
{
	istringstream iss(
		commandLine.substr(commandLine.find('(') + 1, commandLine.find_last_of(')') - commandLine.find('(') - 1)
	);

	copy(istream_iterator<WordDelimitedByCommas>(iss),
		istream_iterator<WordDelimitedByCommas>(),
		back_inserter(Values));

	for (size_t i = 0; i < Values.size(); i++)
	{
		Values[i] = trim(Values[i]);
	}
}

void Insert_Into::padTo(std::string & str, const size_t num, const char paddingChar)
{
	if (num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}
