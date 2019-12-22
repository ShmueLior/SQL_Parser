// Data_Bases_Course.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
#include "SqlParser.h"
#include <map>
#include "Data_Bases_Course.h"
using namespace std;

int main()
{
//	SqlCondition sqlCondition = SqlCondition("(Customers.CustomerName=Orders.CustomerName) AND Orders.Price>1000");

	SqlParser sqlParser = SqlParser("scheme.txt");

	if (sqlParser.IsDataBaseExist())
	{
		//sdcsdc
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
*/