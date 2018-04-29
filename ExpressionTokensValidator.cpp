#include "ExpressionTokensValidator.h"

using namespace std;

ExpressionTokensValidator::ExpressionTokensValidator()
{
}

bool ExpressionTokensValidator::Validate(const std::vector<ExpressionToken>& vecTokens)
{
	int nOpeningParenthesis(0);
	int nConsecutiveOperators(0);
	int nConsecutiveOperands(0);

	// check there are the same number of opening and closing parenthesis
	for(auto i=0; i< vecTokens.size(); ++i)
	{
		auto token = vecTokens[i];

		////////////////////////////////////////////
		// operator
		if (token.IsOperator())
			nConsecutiveOperators++;
		// clear the count
		else
			nConsecutiveOperators = 0;

		// operand
		if (token.IsOperand())
			nConsecutiveOperands++;
		// clear the count
		else
			nConsecutiveOperands = 0;

		// found consecutive operators/operands
		if (nConsecutiveOperators > 1 || nConsecutiveOperands > 1)
			return false;

		/////////////////////////////////////////////
		// operator that is followed by closing parenthesis
		if (token.IsOperator())
		{
			// this is the last token
			if (i == vecTokens.size() - 1)
				return false;
			
			auto nextToken = vecTokens[i + 1];
			if (nextToken.type == RIGHT_BRACKET)
				return false;
		}

		/////////////////////////////////////////////
		// parenthesis
		if (token.IsLeftParenthesis())
			nOpeningParenthesis++;
		else if (token.IsRightParenthesis())
			nOpeningParenthesis--;
	}

	return (nOpeningParenthesis == 0);
}