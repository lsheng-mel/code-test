#include "ExpressionTokensCompiler.h"

using namespace std;

ExpressionTokensCompiler::ExpressionTokensCompiler()
	:ExpressionTokensCompilerBase()
{
}

void ExpressionTokensCompiler::Compile()
{
	Clear();

	// iterate through all tokens in their original order
	for (auto i = 0; i < vecTokens.size(); ++i)
	{
		auto& token(vecTokens[i]);

		switch (token.type)
		{
		case NUMBER:
			// operands
		{
			AddOperand(token);
		}
			break;
		case ADD:
		case SUBTRACT:
		case MULTIPLY:
		case DIVIDE:
			// operators
		{
			// search for any existing operators that comes with higher precedence
			CheckOperatorOfPrecedence(token);
		}
			break;
		case LEFT_BRACKET:
			// opening parenthesis
		{
			AddOperator(token);
		}
			break;
		case RIGHT_BRACKET:
			// closing parenthesis
		{
			// search for an operator backwards and a matching open parenthesis in the operators stack
			if (vecOperators.size() > 0)
			{
				bool bFound(false);
				do
				{
					auto& tokenTmp = vecOperators.back();

					// found an operator
					if (tokenTmp.IsOperator())
					{
						// chuck it into the operands stack
						AddOperand(tokenTmp);

						// pop it off from the operators stack
						vecOperators.pop_back();

						// an opening parenthesis isexpected from the operators stack
						if (vecOperators.back().type == LEFT_BRACKET)
						{
							bFound = true;

							// remove the pair of parenthesis and stack the operator into the operands list
							vecOperators.pop_back();
						}
						else
						{
							// something is wrong?
						}
					}
				} while (vecOperators.size() > 0 && !bFound);
			}
		}
			break;
		default:
			break;
		}
	}

	// push the last bit of operation into the operands stack
	MakeFinalEvaluationStack();
}


bool ExpressionTokensCompiler::CheckOperatorOfPrecedence(const ExpressionToken& token, bool bAdjustTokens/* = true*/)
{
	bool bHighestPrecedence(false);

	if (vecOperators.size() > 0)
	{
		do
		{
			auto& otherOperator = vecOperators.back();

			// something is more important
			if ( otherOperator > token)
			{
				if (bAdjustTokens)
				{
					// push it into the operands stack
					AddOperand(otherOperator);

					// pop it off from the operators stack
					vecOperators.pop_back();
				}
				
			}
			// we are good
			else
			{
				bHighestPrecedence = true;
			}

		} while (vecOperators.size() > 0 && !bHighestPrecedence);
	}
	else
	{
		bHighestPrecedence = true;
	}

	if (bAdjustTokens)
	{
		AddOperator(token);
	}
	
	return bHighestPrecedence;
}

void ExpressionTokensCompiler::MakeFinalEvaluationStack()
{
	while (vecOperators.size() > 0)
	{
		auto& operatorTmp = vecOperators.back();

		// pop off the last operator and push it into the execution stack
		vecOperands.push_back(operatorTmp);

		// remove it from the operators stack
		vecOperators.pop_back();
	}
}