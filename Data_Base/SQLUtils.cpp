#include "SQLUtils.h"

string* SQLUtils::SplitSqlQuery(string i_Query)
{
	string* arr = new string[3];
	arr[0] = i_Query.substr(i_Query.find("SELECT"), i_Query.find("FROM") - i_Query.find("SELECT"));
	arr[0] = StringUtils::RemoveBackSpaceFromEnd(arr[0]);
	arr[1] = i_Query.substr(i_Query.find("FROM"), i_Query.find("WHERE") - i_Query.find("FROM"));
	arr[1] = StringUtils::RemoveBackSpaceFromEnd(arr[0]);
	arr[2] = i_Query.substr(i_Query.find("WHERE"), i_Query.length() - i_Query.find("WHERE") - 1);
	arr[2] = StringUtils::RemoveBackSpaceFromEnd(arr[0]);
	return arr;
}

string SQLUtils::getElements(string sqlString)
{
	int i = 0;
	while (sqlString[i] != ' ')
	{
		if (sqlString[i + 1] == '\0')
		{
			exit(0);
		}
		i++;

	}
	while (sqlString[i] == ' ') { i++; }

	return sqlString.substr(i);
}
