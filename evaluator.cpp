#include<iostream>
#include <String>

#include "ExpressionEvaluator.h"

using namespace std;

int main(int argc, char *argv[])
{
	ExpressionEvaluator evaluator;

	double result(0.0);
	string expression;

	do
	{
		expression.clear();

		// prompt user to input the expression
		cout << "Please enter the expression to evaluate (enter \"exit\" to exit the program):\n\n";
		cin >> expression;

		if (expression == "exit")
			break; 

		if(expression != "")
		{
			// display evaluation result
			evaluator.SetExpression(expression);
			result = evaluator.Evaluate();

			// display error message
			if (!evaluator.IsEvaluationValid())
				cout << "The expression is invalid!\n\n";
			// otherwise display the result
			else
				cout << "The result is:\n\n" << result << "\n\n";
		}
	} while (expression != "");

}