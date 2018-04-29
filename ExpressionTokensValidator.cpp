#include "ExpressionTokensValidator.h"

using namespace std;

ExpressionTokensValidator::ExpressionTokensValidator()
{
}

bool ExpressionTokensValidator::Validate(const std::vector<ExpressionToken>& vecTokens)
{
	if (!AreParenthesisClosed(vecTokens))
		return false;

	if (FindConsectutiveTokens(vecTokens))
		return false;

	return true;
}

bool ExpressionTokensValidator::AreParenthesisClosed(const std::vector<ExpressionToken>& vecTokens)
{
	int nOpeningParenthesis(0);

	// check there are the same number of opening and closing parenthesis
	for each (auto token in vecTokens)
	{
		if (token.IsLeftParenthesis())
			nOpeningParenthesis++;
		else if (token.IsRightParenthesis())
			nOpeningParenthesis--;
	}

	return (nOpeningParenthesis == 0);
}

bool ExpressionTokensValidator::FindConsectutiveTokens(const std::vector<ExpressionToken>& vecTokens)
{
	int nConsecutiveOperators(0);
	int nConsecutiveOperands(0);

	for each (auto token in vecTokens)
	{
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

		if (nConsecutiveOperators > 1 || nConsecutiveOperands > 1)
			return true;
	}

	return false;
}