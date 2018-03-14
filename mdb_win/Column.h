//#include <string>
#pragma once
/*Types
INT
BIT
VARCHAR(*)
*/
//
#define NULLABLE 1
#define NOT_NULL 0

class Column
{
public:
	string Name;
	char Type;
	bool Nullable;
	string Default;
	Column(string arguments);
	~Column();
};

