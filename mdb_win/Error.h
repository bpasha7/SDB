/*
	Error Codes
1xx -
2xx -
3xx -
9xx - DataSetErrors
*/
#pragma once
#include <exception>
#include <string>

using namespace std;

class Error : public exception
{
protected:
	/*Source of error*/
	string Source;
	/*Error message*/
	string Message;
	/*Error code*/
	int Code;
public:
	string GetErrorMessage();
	Error(string source, string message, int code);
	virtual char const * what() const throw();
	~Error();
};

