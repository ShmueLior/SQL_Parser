#include "Attribute.h"

Attribute::Attribute(string i_Name)
{
	m_Name = i_Name;
}

string Attribute::GetName()
{
	return m_Name;
}
