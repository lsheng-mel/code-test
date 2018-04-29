#pragma once
#include "EvaluatorEnums.h"
#include <string>

struct ExpressionToken
{
	ExpressionTokenType type;
	std::string str;
	double value;

	ExpressionToken()
	{
		type = NUMBER;
		str = "";
		value = 0.0;
	}

	//! check if this is an operator
	bool IsOperator()
	{
		return (type == ADD || type == SUBTRACT || type == MULTIPLY || type == DIVIDE);
	}

	//! precedence comparison
	//! NOTE: this is based on assumption that "otherOperator" appears later in the string than this operator
	bool operator>(const ExpressionToken& otherOperator) const
	{
		switch (type)
		{
		case ADD:
		{
			if (otherOperator.type == MULTIPLY || otherOperator.type == DIVIDE)
				return false;

			return true;
		}
			break;
		case SUBTRACT:
		{
			if (otherOperator.type == MULTIPLY || otherOperator.type == DIVIDE)
				return false;

			return true;
		}
			break;
		case MULTIPLY:
		case DIVIDE:
			return true;
			break;
		default:
			break;
		}

		return false;
	}
};