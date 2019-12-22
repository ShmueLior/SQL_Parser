#include "SqlOptimizer.h"

SqlOptimizer::SqlOptimizer(string i_SqlQuery)
{




								// "SELECT R.D,S.E FROM R,S WHERE S.B>4 AND R.A=10";
								
								// PI[R.D,S.E](SIGMA[S.B>4 AND R.A=10](CARTESIAN(R,S)))

}
