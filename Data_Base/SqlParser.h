#define  _CRT_SECURE_NO_WARNINGS

#define SELECT 6
#define FROM 4
#define WHERE 5
#define DISTINCT 8
#define DATA_BASE "scheme.txt"

#include "Table.h"
#include <list>
#include <fstream>
#include <stack>
#include <iostream>
#include <cctype>
#include "SQLUtils.h"
#pragma once

class SqlParser 
{       // The class
	private:
		map <string, Table*> m_tablesMap;
		bool IsValidAttributeList(string i_SelectString);
		bool IsExistAttribute(string i_Attribute);
		Table* GetTable(string i_TableName);
		string IsValidFrom(string i_FromString);
		string IsValidWhere(string i_WhereString);
		string* SplitQuery(string i_Query);
//	string RemoveBackSpaceFromEnd(string i_Str);
//	string trimWhiteSpaces(string sqlString);
//	string getElements(string sqlString);
//	list<Table*> GetTablesFromSchemeFile(string i_FileName);
		void FillTablesFromSchemeFile(string i_FileName);
		string IsValidSelected(string i_SelectString);
		bool IsValidTableList(string i_TableList);
		bool IsExistTable(string i_Table);
		bool IsValidCondition(string i_Condition);
		string IncrementAfterDelimiter(string i_Condition);
		int GetIndexOfCloser(string i_Condition);
		bool IsDistinct(string i_SelectString);
		bool IsValidSimpleCondition(string i_SimpleCondition);
		bool IsAttributeSyntax(string i_Attribute);
		bool IsDigit(string i_Constant);
		string FindRelOp(string i_SimpleCondition);

	public:             // Access specifier
		SqlParser(string i_SchemeName);
		string Parse(string i_Query);
		bool IsDataBaseExist();
};
