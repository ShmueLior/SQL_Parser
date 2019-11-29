#include "FileUtils.h"


int FileUtils::GetNumOfLine(ifstream i_FileStreamReader)
{
	char newLine = '.';
	int numLines = 0;
	string text;



	while (getline(i_FileStreamReader, text, '\n'))
	{
		for (unsigned int i = 0; i < text.length(); i++)
		{
			if (text.at(i) == newLine)
			{
				numLines++;
			}
		}
	}

	return numLines;
}
