#include "SqlOptimizerUI.h"

//enum RULE { 4a = 1, 4, 11b, 6, 5a };

int selectRuleFromUser();

//4,4a, 11b, 6, 5a 

int main()
{
	
	string query = "SELECT R.D,S.E FROM R,S WHERE S.B>4 AND R.A=10";
	
	SqlParser sqlParser = SqlParser("scheme.txt");
	
	string message = sqlParser.Parse(query);

	if (message._Equal("succes"))
	{
		SqlOptimizer optimizer = SqlOptimizer(query);
		//int rule = selectRuleFromUser();
		//invokeRule(rule);
		//string optimizeSql = optimizer.GetAlgebricExpression();
		//displayRuleAndAlgebricExpression(optimizeSql, rule);

	}

	return 0;
	
}

int selectRuleFromUser()
{
	int rule;
	cout << "Select optimze rule:\n1)4\n2)4a\n3)11b\n4)6\n5)5a\n";
	cin >> hex >> rule;

	return rule;
}
