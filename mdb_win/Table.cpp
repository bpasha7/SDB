#include "Table.h"
#include "DataBase.h"
#include "DataSet.h"
#include "Error.h"
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
	_columns.clear();

	_recordLength = 0;

	for (int i = 0; i < columnsCount; i++)
	{
		_columns.push_back(*new Column());
		_columns[i].ReadColumnProperties();
		// count row length
		_recordLength += _columns[i].Size + (_columns[i].Type == '3' ? 4 : 0);
		// calculate column position in a row
		if (i == 0)
			_columns[i].Pos = 0;
		else
		{
			//add 4 bytes if pervious type is char(n)
			_columns[i].Pos = _columns[i - 1].Pos + _columns[i - 1].Size + (_columns[i - 1].Type == '3' ? 4 : 0);
		}
	}

	BinaryStream::Close();
	return 0;
}

int Table::create(Command * sqlCommand)
{
	auto sql = new Create_Table(sqlCommand->text);

	BinaryStream::Create(_dataBaseName, Name, true);
	BinaryStream::Write(sql->CoulumnCount);

	for (int i = 0; i < sql->CoulumnCount; i++)
	{
		sql->Columns[i]->WriteColumnProperties();
	}
	BinaryStream::Close();

	BinaryStream::Create(_dataBaseName, Name, false);
	BinaryStream::Close();

	return 0;
}

int Table::select(Command * sqlCommand)
{
	auto sql = new Select_From(sqlCommand);
	Name = sql->Table;
	getScheme();

	map<long, long> positionsInt;
	map<long, string> positionsString;



	BinaryStream::Open(_dataBaseName, Name, false);
	BinaryStream::SetPosition(0);
	_records.clear();
	int read = 0;
	int counter = 0;

	while (!BinaryStream::EoF())
	{
		Record* record = new Record();
		bool skip = false;//filter flag
		record->Values.clear();
		if (!sql->AllColumns)
		{
			for (size_t i = 0; i < columnsCount; i++)
			{
				if (std::find(sql->ColumnsName.begin(), sql->ColumnsName.end(), _columns[i].Name) == sql->ColumnsName.end())
					_columns[i].Name = "none";
			}
		}
		for (size_t i = 0; i < columnsCount; i++)
		{
			if (!sql->AllColumns && std::find(sql->ColumnsName.begin(), sql->ColumnsName.end(), _columns[i].Name) == sql->ColumnsName.end())
			{
				record->Values.push_back("none");
				continue;
			}
			BinaryStream::SetPosition(counter * _recordLength + _columns[i].Pos);
			switch (_columns[i].Type)
			{
			case '1':
			{
				int val = BinaryStream::ReadInteger();
				if (sql->Filter.size() != 0 && sql->Filter[0] == _columns[i].Name)
				{
					int filterValue = stoi(sql->Filter[2]);
					switch (sql->Filter[1][0])
					{
					case '>':
					{
						skip = val > filterValue ? false : true;
						break;
					}
					case '<':
					{
						skip = val < filterValue ? false : true;
						break;
					}
					case '=':
					{
						skip = val == filterValue ? false : true;
						break;
					}
					default:
						break;
					}
				}
				if (_columns[i].Name == sql->OrderBy)
					positionsInt.insert(pair<long, long>(read, val));
				record->Values.push_back(to_string(val));
				break;
			}
			case '2':
			{
				char val = BinaryStream::ReadChar();
				record->Values.push_back(to_string(val == '0' ? 0 : 1));
				break;
			}
			case '3':
			{
				int length = BinaryStream::ReadInteger();
				string val = BinaryStream::ReadString(length);
				val.erase(remove(val.begin(), val.end(), -63), val.end());
				record->Values.push_back(val);
				if (_columns[i].Name == sql->OrderBy)
					positionsString.insert(pair<long, string>(read, val));
				break;
			}
			default:
				break;
			}
		}
		counter++;
		BinaryStream::SetPosition(counter * _recordLength);

		if (skip)
			continue;
		read++;
		_records.push_back(*record);
		//cout << std::endl;
	}


	BinaryStream::Close();

	if (positionsInt.size() > 0)
	{
		typedef function<bool(pair<long, long>, pair<long, long>)> Comparator;

		Comparator cmp = [](pair<long, long> const & a, pair<long, long> const & b)
		{
			return a.second != b.second ? a.second < b.second : a.first < b.first;
		};

		set<pair<long, long>, Comparator> orderSet(positionsInt.begin(), positionsInt.end(), cmp);

		for (std::pair<long, long> element : orderSet)
			_positions.push_back(element.first);
	}
	if (positionsString.size() > 0) {
		typedef function<bool(pair<long, string>, pair<long, string>)> ComparatorString;

		ComparatorString cmp = [](pair<long, string> const & a, pair<long, string> const & b)
		{
			return a.second != b.second ? a.second < b.second : a.first < b.first;
		};

		set<pair<long, string>, ComparatorString> orderSet(positionsString.begin(), positionsString.end(), cmp);

		for (std::pair<long, string> element : orderSet)
			_positions.push_back(element.first);
	}
	//_columns.erase(std::remove(_columns.begin(), _columns.end(), "none"), _columns.end());
	try
	{
		auto ds = new DataSet(_records.size(), _columns);
		ds->SetRecords(_records);
		showResult(ds);

	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}


	return 0;
}


int Table::insert(Command * sqlCommand)
{
	getScheme();
	auto sql = new Insert_Into(sqlCommand->text);
	try
	{
		BinaryStream::Open(_dataBaseName, Name, false);
		BinaryStream::SetPosition(ios_base::end);
		for (size_t i = 0; i < sql->Values.size(); i++)
		{

			switch (_columns[i].Type)
			{
			case '1':
			{
				int number = stoi(sql->Values[i]);
				//convertor << sql->Values[i];
				//convertor >> number;
				/*if (convertor.fail())
					thrownew exception("Not number"); */
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
				else if (sql->Values[i] == "false" || sql->Values[i] == "0")
					bit = '0';
				else
				{
					errMsg = "Value " + sql->Values[i] + " is not bit!";
					throw new exception();
				}
				BinaryStream::Write(bit);
				break;
			}
			case '3':
			{
				string val = sql->Values[i];
				if (val.length() > _columns[i].Size)
					throw new exception("Not bit");
				sql->padTo(val, _columns[i].Size, 193);
				BinaryStream::Write(_columns[i].Size);
				BinaryStream::Write(val);
				break;
			}

			default:
				break;
			}
		}
		BinaryStream::Close();
	}
	catch (...)
	{
		showError(301, errMsg);
		errMsg = "";
	}
	return 0;
}

void Table::showResult(DataSet * ds)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << endl;


	//
	cout << "| # |";
	for (size_t i = 0; i < ds->Columns(); i++)
	{
		cout << ds->GetColumnFullName(i) << "|";
	}
	cout << endl;
	for (size_t i = 0; i < ds->Count(); i++)
	{
		auto record = ds->GetRecord(i);
		cout << "|" << i + 1 << " |";
		for (size_t j = 0; j < ds->Columns(); j++)
		{
			cout << "\t" << record.Values[j] << "\t" << "|";
		}
		cout << endl;
	}
	/*for (size_t row = 0; row < _records.size(); row++)
	{
		long pos = row;
		if (_positions.size() > 0)
			pos = _positions[pos];
		cout << "|" << row + 1 << "\t" << "|";
		for (size_t i = 0; i < columnsCount; i++)
		{
			switch (_columns[i].Type)
			{
			case '1':
			{
				cout << "\t" << _records[pos].Values[i] << "\t" << "|";
				break;
			}
			case '2':
			{
				cout << "\t" << _records[pos].Values[i] << "\t" << "|";
				break;
			}
			case '3':
			{
				cout << "\t'" << _records[pos].Values[i] << "'\t" << "|";
				break;
			}
			default:
				break;
			}
		}
		cout << endl;
	}*/
	SetConsoleTextAttribute(hConsole, 7);
}
//Errors with table has pattern 3xx
void Table::showError(int errorNumber, string message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cout << "Error (" << errorNumber << "): " << message << endl;
	SetConsoleTextAttribute(hConsole, 7);
}
