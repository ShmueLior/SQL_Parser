#pragma once

#include<string>
#include "Attribute.h"
using namespace std;
class Table {       // The class
private:
	string m_Name;
	Attribute** m_Attributes;
	int m_NumOfAttributes;
	
	
	void parseLine(string i_Line);
	void fillAttributes(string i_AttributeList);
public:             // Access specifier
	Table(string i_Line);
	string GetName();
	bool IsExistAttribute(string i_AttributeName);

};