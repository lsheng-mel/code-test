#include "ExpressionEvaluator.h"

using namespace std;

ExpressionEvaluator::ExpressionEvaluator()
{
	expression = "";
}

void ExpressionEvaluator::SetExpression(string exp)
{
	expression = exp;
}

double ExpressionEvaluator::Evaluate()
{
	// tokenise the expression string
	tokeniser.Tokenise(expression);

	// compile the tokens
	compiler.SetTokens(tokeniser.GetTokens());
	compiler.Compile();

	vector<ExpressionToken> evaluationStack(compiler.GetEvaluationStack());

	return DoEvaluation(evaluationStack);
}

double ExpressionEvaluator::DoEvaluation(vector<ExpressionToken>& evaluationStack)
{
	auto itr = evaluationStack.begin();
	while (itr != evaluationStack.end())
	{
		auto& item = *itr;
		if (item.type == ADD || item.type == SUBTRACT || item.type == MULTIPLY || item.type == DIVIDE)
		{
			// get the two operands in the in front of this operator
			if ((itr - 1) != evaluationStack.end() && (itr - 2) != evaluationStack.end())
			{
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