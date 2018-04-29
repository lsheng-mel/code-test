#pragma once
#include <vector>
#include "ExpressionToken.h"

class ExpressionTokensValidator
{
public:
	ExpressionTokensValidator();

public:
	bool Validate(const std::vector<ExpressionToken>& vecTokens);

private:
	//! check if all parenthesis are closed properly
	bool AreParenthesisClosed(const std::vector<ExpressionToken>& vecTokens);

	//! check if there is any consecutive operators/operands
	bool FindConsectutiveTokens(const std::vector<ExpressionToken>& vecTokens);
};
