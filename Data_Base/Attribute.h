#include<string>

using namespace std;
class Attribute {       // The class
private:
	string m_Name;

public:
	Attribute(string i_Name);
	string GetName();
};
