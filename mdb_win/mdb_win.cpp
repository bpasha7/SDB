// mdb_win.cpp : Defines the entry point for the console application.
//

#include "DataBase.h"
//#include "stdafx.h"


int main()
{
	DataBase* dataBase;
	dataBase = new DataBase();
	dataBase->Start();
    return 0;
}