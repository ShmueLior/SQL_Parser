// Data_Bases_Course.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SqlParser.h"

using namespace std;

int main()
{
	SqlParser sqlParser = SqlParser("scheme.txt");

	if (sqlParser.IsDataBaseExist())
	{
		string succesParsing;
		cout << "Plesae enter your sql query Below!\n";
		string query;
		getline(cin, query);
		succesParsing = sqlParser.Parse(query);
		if (succesParsing._Equal("succes"))
		{
			cout << "The Query:" + query + "Parsed Succesfuly!\n";
		}
		else
		{
			cout << "Parsing --> '" + succesParsing + "' Failed\n";
		}
	}


	return 0;
}
