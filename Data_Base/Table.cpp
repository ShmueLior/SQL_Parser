#include "Table.h"
#include <iostream>
#include "StringUtils.h"

void Table::parseLine(string i_Line)
{
	m_Name = i_Line.substr(0, i_Line.find('('));
	m_NumOfAttributes = std::count(i_Line.begin(), i_Line.end(), ',') + 1;
	m_Attributes = new Attribute*[m_NumOfAttributes];

	i_Line = i_Line.substr(i_Line.find('(') + 1);
	fillAttributes(i_Line);

}

void Table::fillAttributes(string i_AttributeList)
{
	// CustomerName:STRING, Age:INTEGER)
	int i = 0;
	i_AttributeList = StringUtils::Trim(i_AttributeList);

	bool finished = false;
	while (!finished)
	{
		string attributeName = i_AttributeList.substr(0, i_AttributeList.find(':'));
		m_Attributes[i] = new Attribute(attributeName);
		string tempAttributeList = i_AttributeList.substr(i_AttributeList.find(',') + 1);
		if (tempAttributeList._Equal(i_AttributeList)) // mean find didnt work, we are in the end
		{
			finished = true;

		}
		i_AttributeList = tempAttributeList;
		i++;
	}
}

Table::Table(string i_Line)
{
	parseLine(i_Line);
}

string Table::GetName()
{
	return m_Name;
}

bool Table::IsExistAttribute(string i_AttributeName)
{
	bool isExistAttribute = false;
	for (int i = 0; i < m_NumOfAttributes; i++)
	{
		if (m_Attributes[i]->GetName()._Equal(i_AttributeName))
		{
			isExistAttribute = true;
		}
	}

	return isExistAttribute;
}
