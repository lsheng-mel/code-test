#include "ExpressionEvaluator.h"
#include <math.h>

using namespace std;

ExpressionEvaluator::ExpressionEvaluator()
{
	expression = "";
	SetValid(true);
}

void ExpressionEvaluator::SetExpression(string exp)
{
	expression = exp;
}

double ExpressionEvaluator::Evaluate()
{
	const double invalidResult(0.0);

	// tokenise the expression string
	if (tokeniser.Tokenise(expression))
	{
		// validate the tokens before moving forward
		SetValid(validator.Validate(tokeniser.GetTokens()));

		// proceed with the evaluation
		if (bValid)
		{
			// compile the tokens
			compiler.SetTokens(tokeniser.GetTokens());
			compiler.Compile();

			return DoEvaluation(compiler.GetEvaluationStack());
		}
	}
	else
	{
		SetValid(false);
	}	

	return invalidResult;
}

double ExpressionEvaluator::DoEvaluation(const vector<ExpressionToken>& stack)
{
	vector<ExpressionToken> evaluationStack(stack);

	auto itr = evaluationStack.begin();
	while (itr != evaluationStack.end())
	{
		auto& item = *itr;
		if (item.IsOperator())
		{
			// check to ensure there are two operands in front of this operator before moving on
			if (evaluationStack.begin() + 1 != evaluationStack.end() && itr >= evaluationStack.begin() + 1)
			{
				// get the two operands in the in front of this operator
				auto& operand1 = *(itr - 1);
				auto& operand2 = *(itr - 2);

				if (operand1.type == NUMBER && operand2.type == NUMBER)
				{
					double val(0.0);
					switch (item.type)
					{
					case ADD:
					{
						val = operand1.value + operand2.value;
					}
						break;
					case SUBTRACT:
					{
						val = operand2.value - operand1.value;
					}
						break;
					case MULTIPLY:
					{
						val = operand1.value * operand2.value;
					}
						break;
					case DIVIDE:
					{
						// make sure it doesn't go nuts
						if(operand1.value != 0.0)
							val = operand2.value / operand1.value;
						else
							return 0.0;
					}
						break;
					case POWER:
						if (operand1.value == 0.0)
							val = 1.0;
						else if (operand2.value == 0.0)
							val = 0.0;
						else
						{
							val = pow(operand2.value, operand1.value);
						}
						break;
					default:
						break;
					}

					// we are done with the operator and the second operand, they need to be removed out of the stack now
					itr = evaluationStack.erase(itr);
					itr = evaluationStack.erase(itr - 1);

					// update the first operand to have the calculated value
					auto& updatedOperand = *(itr - 1);
					updatedOperand.value = val;
				}
			}
			
		}
		// move on to the next one
		else
		{
			itr++;
		}
	}

	if (evaluationStack.size() == 1 && evaluationStack[0].type == NUMBER)
	{
		return evaluationStack[0].value;
	}

	return 0.0;
}