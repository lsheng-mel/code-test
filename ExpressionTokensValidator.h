#pragma once
#include <vector>
#include "ExpressionToken.h"

class ExpressionTokensValidator
{
public:
	ExpressionTokensValidator();

public:
	bool Validate(const std::vector<ExpressionToken>& vecTokens);
};
