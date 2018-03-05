#include "stdafx.h"
#include "Command.h"


Command::Command(string commandLine)
{
	istringstream iss(commandLine);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(Words));
}

Command::~Command()
{
}
