#include "stdafx.h"
#include "Column.h"


Column::Column(string arguments)
{
	vector<string> splited;

	istringstream iss(arguments);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(splited));

	if (splited.size() > 1)
		Name = splited[0];
	/*for (int i = 0; i < splited.size(); i++)
	{
		auto column = new Column(splited[i]);
	}*/
}


Column::~Column()
{
}
