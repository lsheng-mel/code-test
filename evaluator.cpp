#include<iostream>
#include <String>

#include "ExpressionEvaluator.h"

using namespace std;

int main(int argc, char *argv[])
{
	const string expresion1("1+1");
	const string expresion2("1.1+1.1");
	const string expresion3("2+25*4");
	const string expresion4("(2+25)*4.3");
	const string expresion5("54/((2+25/3*(3.2+15.6))*4)+1.25*2-5.6");
	const string expresion6("(((3+33.456*12.3)/22)+2.4)-(65.21/10.34)");
	const string expresion7("((((3+33.456*12.3)/22)+2.4)-65.21)/10.34");
	const string expresion8("54/((2+25/3*(3.2+15.6))*4)+1.25*2-5.6");
	const string expresion9("54/((2+25/3*(3.2+15.6))*4)+1.25*2-5.6");
	const string expresion10("3^3");
	const string expresion11("-1-1");
	const string expresion12("-(2+2)");

	ExpressionEvaluator evaluator;
	evaluator.SetExpression(expresion5);

	printf("The evaluation result of expresion \"%s\" is:\n %f\n", expresion5.c_str(), evaluator.Evaluate());

	double answer(54.0 / ((2.0 + 25.0 / 3.0 * (3.2 + 15.6)) * 4.0) + 1.25 * 2.0 - 5.6);
	printf("The correct answer is: %f\n", answer);

	system("pause");
}