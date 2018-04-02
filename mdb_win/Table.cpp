#include "Table.h"
#include "DataBase.h"
#include "BinaryStream.h"

//#include <list>

Table::Table(string dataBaseName, string tableName)
{
	_dataBaseName = dataBaseName;
	//cls = make_shared<Column>(12);
	Name = tableName;
	if (isTableExist())
	{

	}
}

int Table::DoSqlCommand(Command * sqlCommand)
{
	if (sqlCommand->Words[0] == "create" && sqlCommand->Words[1] == "table")
	{
		create(sqlCommand);
		return 1;
	}
	/*if (!isTableExist())
	{
		return -1;
	}*/
	if (sqlCommand->Words[0] == "select")
	{
		select(sqlCommand);
	}
	if (sqlCommand->Words[0] == "insert")
	{
		insert(sqlCommand);
	}
	return 0;
}

Table::~Table()
{
}

bool Table::isTableExist()
{
	std::ifstream ifile(_directory + _dataBaseName + "\\" + Name + ".dt");
	return (bool)ifile;
}

int Table::getScheme()
{
	columnsCount = 0;
	BinaryStream::Open(_dataBaseName, Name, true);
	BinaryStream::SetPosition(0);

	columnsCount = BinaryStream::ReadInteger();
	_columns = new Column *[columnsCount];

	for (int i = 0; i < columnsCount; i++)
	{
		_columns[i] = new Column();
		_columns[i]->ReadColumnProperties();
	}

	BinaryStream::Close();
	return 0;
}

int Table::create(Command * sqlCommand)
{
	//string path = _directory + _dataBaseName + "\\" + Name + ".df";
	//_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
	auto sql = new Create_Table(sqlCommand->text);

	/*	int t = _dataBaseStream.tellp();
		_dataBaseStream.seekp(0);
		t = */
		//start from the beginig
		//_dataBaseStream.tellp();

	BinaryStream::Create(_dataBaseName, Name, true);
	BinaryStream::Write(sql->CoulumnCount);

	for (int i = 0; i < sql->CoulumnCount; i++)
	{
		sql->Columns[i]->WriteColumnProperties();
	}
	BinaryStream::Close();

	//_dataBaseStream.close();

	BinaryStream::Create(_dataBaseName, Name, false);
	BinaryStream::Close();
	//path = _directory + _dataBaseName + "\\" + Name + ".dt";
	//_dataBaseStream.open(path, ios::binary | ios::out | ios::app);
	//_dataBaseStream.close();
	return 0;
}

int Table::select(Command * sqlCommand)
{
	auto sql = new Select_From(sqlCommand);
	Name = sql->Table;
	getScheme();


	BinaryStream::Open(_dataBaseName, Name, false);
	BinaryStream::SetPosition(0);
	_records.clear();
	int counter = 1;
	while (!BinaryStream::EoF())
	{
		Record* record = new Record();
		record->Values.clear();
		//cout << "|\t" << counter++ << "\t" << "|";
		for (size_t i = 0; i < columnsCount; i++)
		{
			switch (_columns[i]->Type)
			{
			case '1':
			{
				int val = BinaryStream::ReadInteger();
				record->Values.push_back(to_string(val));
				//cout << "\t" << BinaryStream::ReadInteger() << "\t" << "|";
				break;
			}
			case '2':
			{
				char val = BinaryStream::ReadChar();
				record->Values.push_back(to_string(val == '0' ? 0 : 1));
				//cout << "\t" << BinaryStream::ReadChar() << "\t" << "|";
				break;
			}
			case '3':
			{
				int length = BinaryStream::ReadInteger();
				string val = BinaryStream::ReadString(length);
				val.erase(std::remove(val.begin(), val.end(), -63), val.end());
				record->Values.push_back(val);
				//cout << "\t" << val << "\t" << "|";
				break;
			}
			default:
				break;
			}
		}
		_records.push_back(*record);
		//cout << std::endl;
	}

	BinaryStream::Close();
	showResult();


	return 0;
}

int Table::insert(Command * sqlCommand)
{
	getScheme();
	auto sql = new Insert_Into(sqlCommand->text);
	BinaryStream::Open(_dataBaseName, Name, false);
	BinaryStream::SetPosition(ios_base::end);
	std::stringstream convertor;
	for (size_t i = 0; i < sql->Values.size(); i++)
	{
		try
		{
			switch (_columns[i]->Type)
			{
				case '1':
				{
					int number;
					convertor << sql->Values[i];
					convertor >> number;
					if (convertor.fail())
						throw new exception("Not number");
					BinaryStream::Write(number);
					break;
				}
				case '2':
				{
					char bit;
					/*convertor << sql->Values[i];
					convertor >> bit;*/
					
					if (sql->Values[i] == "true" || sql->Values[i] == "1")
						bit = '1';
					else if(sql->Values[i] == "false" || sql->Values[i] == "0")
						bit = '0';
					else
						throw new exception("Not bit");
					BinaryStream::Write(bit);
					break;
				}
				case '3':
				{
					string val = sql->Values[i];
					if(val.length() > _columns[i]->Size)
						throw new exception("Not bit");
					sql->padTo(val, _columns[i]->Size, 193);
					BinaryStream::Write(_columns[i]->Size);
					BinaryStream::Write(val);
					break;
				}

			default:
				break;
			}
			//BinaryStream::Write(sql->Values[i]);

		}
		catch (...)
		{
			/* ... */
		}
		//_dataBaseStream.write(sql->Values[i].c_str(), sql->Values[i].length());
	}
	BinaryStream::Close();
	return 0;
}

void Table::showResult()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << std::endl;
	//Вывод название полей
	cout << "|\t" << "#" << "\t" << "|";
	for (size_t i = 0; i < columnsCount; i++)
	{
		cout << "\t" << _columns[i]->Name << "\t" << "|";
	}
	cout << std::endl;
	for (size_t row = 0; row < _records.size(); row++)
	{
		cout << "|\t" << row + 1 << "\t" << "|";
		for (size_t i = 0; i < columnsCount; i++)
		{
			switch (_columns[i]->Type)
			{
			case '1':
			{
				cout << "\t" << _records[row].Values[i] << "\t" << "|";
				break;
			}
			case '2':
			{
				cout << "\t" << _records[row].Values[i] << "\t" << "|";
				break;
			}
			case '3':
			{
				cout << "\t'" << _records[row].Values[i] << "'\t" << "|";
				break;
			}
			default:
				break;
			}
		}
		cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
}
