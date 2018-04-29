#pragma once
#include <string>
#include "EvaluatorEnums.h"

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
		return (type == ADD || type == SUBTRACT || type == MULTIPLY || type == DIVIDE || type == POWER);
	}
	
	//! check if this is an operand
	bool IsOperand()
	{
		return (type == NUMBER);
	}

	//! check if this is a left parenthesis
	bool IsLeftParenthesis()
	{
		return (type == LEFT_BRACKET);
	}

	//! check if this is a right parenthesis
	bool IsRightParenthesis()
	{
		return (type == RIGHT_BRACKET);
	}

	//! precedence comparison
	//! NOTE: this is based on assumption that "otherOperator" appears later in the string than this operator
	bool operator>(const ExpressionToken& otherOperator) const
	{
		switch (type)
		{
		case ADD:
		{
			if (otherOperator.type == MULTIPLY || otherOperator.type == DIVIDE || otherOperator.type == POWER)
				return false;

			return true;
		}
			break;
		case SUBTRACT:
		{
			if (otherOperator.type == MULTIPLY || otherOperator.type == DIVIDE || otherOperator.type == POWER)
				return false;

			return true;
		}
			break;
		case MULTIPLY:
		case DIVIDE:
			if(otherOperator.type != POWER)
				return true;
			break;
		case POWER:
			return true;
			break;
		default:
			break;
		}

		return false;
	}
};