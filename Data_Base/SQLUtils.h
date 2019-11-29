#pragma once
#include <string>
using namespace std;
static class SQLUtils
{

public:
	static bool isValidSelect(string i_SelectString);
	static bool isValidFrom(string i_FromString);
	static bool isValidWhere(string i_WhereString);
};


