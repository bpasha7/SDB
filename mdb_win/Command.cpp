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
	auto from = find(command->Words.begin(), command->Words.end(), "from") - command->Words.begin();
	if (command->Words[1] == "*")
		AllColumns = true;
	else
	{
		ColumnsName.clear();
		for (size_t i = 1; i < from; i++)
		{
			int comma = command->Words[i].find(",");
			auto name = command->Words[i];

			ColumnsName.push_back(comma != string::npos ? command->Words[i].erase(comma, 1) : command->Words[i]);
		}
	}
	//std::vector<string>::iterator it;
	//if word from not exist
	if (from >= command->Words.size()) {
		//old_name_ not found
	}
	//not contain table name
	if ((int)from + 1 > command->Words.size())
	{

	}
	Table = command->Words[from + 1];

	auto orderBy = find(command->Words.begin(), command->Words.end(), "order") - command->Words.begin();
	if (orderBy != command->Words.size())
	{
		OrderBy = command->Words[orderBy + 2];
	}
	command->Words.erase(command->Words.begin() + orderBy, command->Words.begin() + orderBy + 3);
	//command->Words.pop_back(pos + 1);
	//command->Words.pop_back(pos + 2);

	auto where = find(command->Words.begin(), command->Words.end(), "where") - command->Words.begin();
	if (where != command->Words.size())
	{
		Filter.clear();
		//check length
		if ((command->Words.size() - where) % 4 == 0)
		{
			for (size_t i = where + 1; i < command->Words.size(); i+=4)
			{
				Filter.push_back(command->Words[i]);
				Filter.push_back(command->Words[i + 1]);
				Filter.push_back(command->Words[i + 2]);
				if(i + 3 != command->Words.size())
					Filter.push_back(command->Words[i + 3]);
			}
		}
		else if ((command->Words.size() - where) == 3)
		{
			Filter.push_back(command->Words[where + 1]);
			Filter.push_back(command->Words[where + 2]);
			Filter.push_back(command->Words[where + 3]);
		}

	}

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
