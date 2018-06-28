#include "Error.h"


string Error::GetErrorMessage()
{
	return "(" + to_string(Code) + ")" + Source + ": " + Message + "!";
}

Error::Error(string source, string message, int code)
{
	this->Source = source;
	this->Message = message;
	this->Code = code;
}
char const * Error::what() const throw()
{
#pragma warning(disable : 4996)
	string text = ("(" + std::to_string(this->Code) + ")" + this->Source + ": " + this->Message);
	char* buf = new char[(int)(text.size() + 1)];
	// char buf = new char[(int)(text.size() + 1)];
	buf[0] = '\0';
	strcat(buf, "(");
	strcat(buf, std::to_string(this->Code).c_str());
	strcat(buf, ") ");
	strcat(buf, this->Source.c_str());
	strcat(buf, ": ");
	strcat(buf, this->Message.c_str());


	return buf;
}

Error::~Error()
{
}
