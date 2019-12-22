#include "Attribute.h"
#include "StringUtils.h"
#include <map>

class Table {       // The class
private:
	string m_Name;
	map <string, Attribute> m_AttributesMap;
	//Attribute** m_Attributes;
	//int m_NumOfAttributes;
	
	
	void parseLine(string i_Line);
	void fillAttributes(string i_AttributeList);
public:             // Access specifier
	Table(string i_Line);
	string GetName();
	bool IsExistAttribute(string i_AttributeName);

};