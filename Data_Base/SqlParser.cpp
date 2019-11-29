#define  _CRT_SECURE_NO_WARNINGS

#define SELECT 6
#define FROM 4
#define WHERE 5
#define DISTINCT 8
#define DATA_BASE "scheme.txt" 

#include "SqlParser.h"

SqlParser::SqlParser(string i_SchemeName)
{
	m_Tables = GetTablesFromSchemeFile(i_SchemeName);
}

string SqlParser::Parse(string i_Query)
{
	string* arr = SplitQuery(i_Query);

	string res;

	string isValidFrom = IsValidFrom(arr[1]);
	res = isValidFrom;
	if (isValidFrom._Equal("succes"))
	{
		string isValidSelect = IsValidSelected(arr[0]);
		res = isValidSelect;
		if (isValidSelect._Equal("succes"))
		{
			string isValidWhere = IsValidWhere(arr[2]);
			res = isValidWhere;
		}
	}

	return res;
}

//SELECT
string SqlParser::IsValidSelected(string i_SelectString) //Select           x,  y , z
{
	bool isValidSelected = true;
	string isValidSelectedUI;

	string attributeList = getElements(i_SelectString);

	bool isDistinct = IsDistinct(attributeList);

	if (isDistinct)
	{
		attributeList = attributeList.substr(DISTINCT + 1);
	}

	attributeList = trimWhiteSpaces(attributeList);

	bool isAllSelected = attributeList._Equal("*");

	if (!isAllSelected)
	{
		isValidSelected = IsValidAttributeList(attributeList);
	}

	if (isValidSelected | isAllSelected)
	{
		isValidSelectedUI = "succes";
	}
	else
	{
		isValidSelectedUI = attributeList;
	}

	return isValidSelectedUI;
}

bool SqlParser::IsDistinct(string i_SelectString)
{
	string delimiter = " ";
	string firstElement = i_SelectString.substr(0, i_SelectString.find(delimiter));
	return firstElement._Equal("DISTINCT");
}

bool SqlParser::IsValidAttributeList(string i_AttributeList)
{
	bool isValidAttributeList;

	string delimiter = ",";
	string attribute = i_AttributeList.substr(0, i_AttributeList.find(delimiter));
	bool isExistAttribute = IsExistAttribute(attribute); 

	if (attribute.size() + 1 < i_AttributeList.size())
	{
		i_AttributeList = i_AttributeList.substr(attribute.length() + 1);
		isValidAttributeList = isExistAttribute && IsValidAttributeList(i_AttributeList);
	}
	else
	{
		isValidAttributeList = isExistAttribute;
	}
	return isValidAttributeList;
}

bool SqlParser::IsExistAttribute(string i_Attribute)
{
	string tableName = i_Attribute.substr(0, i_Attribute.find('.'));
	string attributeName = i_Attribute.substr(tableName.length() + 1);
	bool isExistAttribute = false;

	Table* table = GetTable(tableName);
	if (table != NULL)
	{
		isExistAttribute = table->IsExistAttribute(attributeName);
	}
	return isExistAttribute;
}

//FROM
string SqlParser::IsValidFrom(string i_FromString)
{
	string isValidFrom = "succes";
	string tableList = getElements(i_FromString);
	tableList = trimWhiteSpaces(tableList);
	if (!IsValidTableList(tableList))
	{
		isValidFrom = tableList;
	}

	return isValidFrom;
}

bool SqlParser::IsValidTableList(string i_TableList)
{
	bool isValidTableList;
	string delimiter = ",";
	string table = i_TableList.substr(0, i_TableList.find(delimiter));

	bool isExistTable = IsExistTable(table);
	if (table.size() + 1 < i_TableList.size())
	{
		i_TableList = i_TableList.substr(table.length() + 1);
		isValidTableList = isExistTable && IsValidTableList(i_TableList);
	}
	else
	{
		isValidTableList = isExistTable;
	}

	return isValidTableList;
}

bool SqlParser::IsExistTable(string i_Table)
{
	bool isExist = false;
	for (Table* table : m_Tables)
	{
		if (table->GetName()._Equal(i_Table))
		{
			isExist = true;
		}
	}
	return isExist;
}

//WHERE
string SqlParser::IsValidWhere(string i_WhereString)
{
	bool isValidWhere = true;
	string isValidWhereUI;

	string condition = i_WhereString.substr(WHERE + 1, i_WhereString.size());

	isValidWhere = IsValidCondition(condition);

	if (isValidWhere)
	{
		isValidWhereUI = "succes";
	}
	else
	{
		isValidWhereUI = condition;
	}

	return isValidWhereUI;
}

bool SqlParser::IsValidCondition(string i_Condition)
{
	bool isValidCondition = false;
	string andDelimiter = "AND";
	string orDelimiter = "OR";
	string delimiter;
	if (i_Condition[0] == '\0')
	{
		isValidCondition = true;
	}
	else if (i_Condition[0] == '(')
	{
		int indexOfCloser = GetIndexOfCloser(i_Condition);
		if (indexOfCloser != -1)
		{
			string subConidtionWithOutBrackets = i_Condition.substr(1, indexOfCloser - 1);
			isValidCondition = IsValidCondition(subConidtionWithOutBrackets);

			i_Condition = i_Condition.substr(indexOfCloser);
			string tempCondition = IncrementAfterDelimiter(i_Condition);
			if (!tempCondition._Equal(i_Condition))
			{
				i_Condition = tempCondition;
				isValidCondition = isValidCondition && IsValidCondition(i_Condition);
			}
			// esle maybe end of condition or problem
		}
	}
	else
	{
		string simpleCondition;
		int delimiterLength;
		if (i_Condition.find(orDelimiter) > i_Condition.find(andDelimiter))
		{
			simpleCondition = i_Condition.substr(0, i_Condition.find(andDelimiter) - 1);
			delimiterLength = 4;
		}
		else if (i_Condition.find(orDelimiter) < i_Condition.find(andDelimiter))
		{
			simpleCondition = i_Condition.substr(0, i_Condition.find(orDelimiter) - 1);
			delimiterLength = 3;
		}
		else
		{
			simpleCondition = i_Condition;
		}

		isValidCondition = IsValidSimpleCondition(simpleCondition); // check if exist; 

		if (simpleCondition.size() + 1 < i_Condition.size())
		{
			i_Condition = i_Condition.substr(simpleCondition.length() + delimiterLength + 1);
			isValidCondition = isValidCondition && IsValidCondition(i_Condition);
		}

	}
	return isValidCondition;
}

int SqlParser::GetIndexOfCloser(string i_Condition)
{
	stack <char> s;
	s.push('(');
	int indexOfCloser = -1;
	int i = 1;
	while (!s.empty() && i < i_Condition.length())
	{

		if (i_Condition[i] == ')')
			s.pop();
		if (i_Condition[i] == '(')
		{
			s.push('(');
		}

		i++;
	}
	if (s.empty())
	{
		indexOfCloser = i - 1;
	}
	else
	{
		indexOfCloser = -1;
	}

	return indexOfCloser;
}

string SqlParser::IncrementAfterDelimiter(string i_Condition)
{
	if (i_Condition.find("AND") > i_Condition.find("OR"))
	{
		i_Condition = i_Condition.substr(i_Condition.find("OR") + 3);
	}
	else if (i_Condition.find("AND") < i_Condition.find("OR"))
	{
		i_Condition = i_Condition.substr(i_Condition.find("AND") + 4);
	}

	return i_Condition;
}

bool SqlParser::IsValidSimpleCondition(string i_SimpleCondition)
{
	bool isValidSimpleCondition = false;
	bool isExistRelOp = false;
	bool isExistAttributeConstant1 = false;
	bool isExistAttributeConstant2 = false;
	bool isDigitConstant1 = false;
	bool isDigitConstant2 = false;
	bool isValidConstant1 = false;
	bool isValidConstant2 = false;
	string delimiter = FindRelOp(i_SimpleCondition);
	if (delimiter != "")
	{
		isExistRelOp = true;
		string constant1 = i_SimpleCondition.substr(0, i_SimpleCondition.find(delimiter));
		string constant2 = i_SimpleCondition.substr(constant1.length() + delimiter.length());
		if (IsAttributeSyntax(constant1))
		{
			isExistAttributeConstant1 = IsExistAttribute(constant1);
		}
		else
		{
			isDigitConstant1 = IsDigit(constant1);
		}

		if (IsAttributeSyntax(constant2))
		{
			isExistAttributeConstant2 = IsExistAttribute(constant1);
		}
		else
		{
			isDigitConstant2 = IsDigit(constant2);
		}
	}
	else
	{
		isExistRelOp = false;
	}

	isValidConstant1 = isExistAttributeConstant1 || isDigitConstant1;
	isValidConstant2 = isExistAttributeConstant2 || isDigitConstant2;
	isValidSimpleCondition = isValidConstant1 && isValidConstant2 && isExistRelOp;

	return isValidSimpleCondition;
}

string SqlParser::FindRelOp(string i_SimpleCondition)
{
	string relOp = "";

	int indexOfBigger = i_SimpleCondition.find(">");
	int indexOfSmaller = i_SimpleCondition.find("<");
	int indexOfBiggerEqual = i_SimpleCondition.find(">=");
	int indexOfSmallerEqual = i_SimpleCondition.find("<=");
	int indexOfNotEqual = i_SimpleCondition.find("<>");
	int indexOfEqual = i_SimpleCondition.find("=");

	if (indexOfBiggerEqual != -1)
	{
		relOp = ">=";
	}
	else if (indexOfSmallerEqual != -1)
	{
		relOp = "<=";
	}
	else if (indexOfNotEqual != -1)
	{
		relOp = "<>";
	}
	else if (indexOfEqual != -1)
	{
		relOp = "=";
	}
	else if (indexOfBigger != -1)
	{
		relOp = ">";
	}
	else if (indexOfSmaller != -1)
	{
		relOp = "<";
	}


	return relOp;
}

bool SqlParser::IsAttributeSyntax(string i_Attribute)
{
	return i_Attribute.find('.') != -1;
}

bool SqlParser::IsDigit(string i_Constant)
{
	bool isDigit;
	if (i_Constant[0] != '\0')
	{
		isDigit = isdigit(i_Constant[0]) != 0 && IsDigit(i_Constant.substr(1));
	}
	else
	{
		isDigit = true;
	}

	return isDigit;
}

//UTILS
Table* SqlParser::GetTable(string i_TableName)
{
	Table* tableRes = NULL;
	for (Table* table : m_Tables)
	{
		if (table->GetName()._Equal(i_TableName))
		{
			tableRes = table;
		}
	}

	return tableRes;
}

string* SqlParser::SplitQuery(string i_Query)
{
	string* arr = new string[3];
	arr[0] = i_Query.substr(i_Query.find("SELECT"), i_Query.find("FROM") - i_Query.find("SELECT"));
	arr[0] = RemoveBackSpaceFromEnd(arr[0]);
	arr[1] = i_Query.substr(i_Query.find("FROM"), i_Query.find("WHERE") - i_Query.find("FROM"));
	arr[1] = RemoveBackSpaceFromEnd(arr[1]);
	arr[2] = i_Query.substr(i_Query.find("WHERE"), i_Query.length() - i_Query.find("WHERE") - 1);
	arr[2] = RemoveBackSpaceFromEnd(arr[2]);
	return arr;
}

string SqlParser::RemoveBackSpaceFromEnd(string i_Str)
{
	int i = i_Str.length() - 1;
	while (i_Str[i] == ' ')
	{
		i--;
	}
	return i_Str.substr(0, i + 1);
}

string SqlParser::trimWhiteSpaces(string sqlString)
{
	int i = 0;
	int count = 0;
	while (sqlString[i] != '\0')
	{
		if (sqlString[i] != ' ')
		{
			sqlString[count++] = sqlString[i];
		}
		i++;
	}

	sqlString[count] = '\0';
	sqlString = sqlString.substr(0, sqlString.find('\0'));

	return sqlString;
}

string SqlParser::getElements(string sqlString)
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

list<Table*> SqlParser::GetTablesFromSchemeFile(string i_FileName)
{
	list <Table*> tables;
	ifstream fileStreamReader(i_FileName);
	if (fileStreamReader.is_open())
	{
		string line;
		while (getline(fileStreamReader, line))
		{											 //read data from file object and put it into string.
			//cout << line << "\n"; //print the data of the string
			tables.push_back(new Table(line));
		}
		fileStreamReader.close();
	}
	else
	{
		cout << "Unable to open file";
	};

	return tables;
}

bool SqlParser::IsDataBaseExist()
{
	return m_Tables.size() != 0;
}
