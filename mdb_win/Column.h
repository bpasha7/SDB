//#include <string>
#pragma once
/*Types
INT
BIT
VARCHAR(*)
*/
//
#define NULLABLE 1
#define NOTNULL 0

class Column
{
public:
	string Name;
	string Type;
	bool Nullable;
	string Default;
	Column();
	~Column();
};

