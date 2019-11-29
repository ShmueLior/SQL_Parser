#include "StringUtils.h"

string StringUtils::Trim(string i_Str)
{
	int i = 0;
	int count = 0;
	while (i_Str[i] != '\0')
	{
		if (i_Str[i] != ' ')
		{
			i_Str[count++] = i_Str[i];
		}
		i++;
	}

	i_Str[count] = '\0';
	i_Str = i_Str.substr(0, i_Str.find('\0'));

	return i_Str;
}
