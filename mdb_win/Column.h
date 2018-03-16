#pragma once
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>

using namespace std;

/*Types
INT 1
BIT - 2
VARCHAR(*) - 3
*/
//
#define NULLABLE 1
#define NOT_NULL 0

class Column
{
public:
	string Name;
	char Type;
	int Size;
	/*bool Nullable;
	string Default;*/
	Column(string arguments);
	Column(fstream *stream);
	int WriteColumnProperties(fstream *stream);
	~Column();
private:
	int parseType(string type);


	int writeBinaryToSrteam(fstream * stream, char value);
	int writeBinaryToSrteam(fstream * stream, int value);
	int writeBinaryToSrteam(fstream * stream, string value);
};

