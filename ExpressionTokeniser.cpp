#include <math.h>
#include "ExpressionTokeniser.h"

using namespace std;

ExpressionTokeniser::ExpressionTokeniser()
{
}

bool ExpressionTokeniser::Tokenise(string expression)
{
	if (expression == "")
		return false;

	// start from scratch
	ClearTokens();

	// reset current operand
	operand.clear();

	// iterate each character within the string
	for (auto i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];
	
		// ignore spaces
		if (c == ' ')
			continue;

		// continue on the current operand traverse if it is still related
		// otherwise move on
		if(!UpdateCurrentOperand(c))
		{
			// try to collect a unary operator
			if (!CollectUnaryOperator(c))
			{
				// try to collect an operator
				if (!CollectOperator(c))
				{
					// try to collect a bracket
					if (!CollectBracket(c))
						return false;
				}
			}
		}
		// if it is an operand for the last run, then we need to collect it to finish the iteration
		else if (i == expression.length() - 1)
		{
			CollectOperand();
		}
	}

	return true;
}

int ExpressionTokeniser::toNumber(char c)
{
	int ret = c - '0';
	return ret;
}

bool ExpressionTokeniser::IsNumber(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}

	return false;
}

bool ExpressionTokeniser::IsDecimal(char c)
{
	if (c == '.')
	{
		return true;
	}

	return false;
}

bool ExpressionTokeniser::IsLeftBracket(char c)
{
	const char leftBracket('(');

	if (c == leftBracket)
	{
		return true;
	}

	return false;
}

bool ExpressionTokeniser::IsRightBracket(char c)
{
	const char rightBracket(')');

	if (c == rightBracket)
	{
		return true;
	}

	return false;
}

bool ExpressionTokeniser::IsBracket(char c)
{
	return (IsLeftBracket(c) || IsRightBracket(c));
}

bool ExpressionTokeniser::IsOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
	{
		return true;
	}

	return false;
}

bool ExpressionTokeniser::IsUnaryOperator(char c)
{
	if (c == '+' || c == '-')
	{
		// nothing is in the front
		if (vecTokens.size() == 0)
			return true;

		auto& tokenPrevious = vecTokens.back();

		// it is a unary operator if it is an operator or opening parenthesis in front of it 
		if (tokenPrevious.type == ADD
			|| tokenPrevious.type == SUBTRACT
			|| tokenPrevious.type == MULTIPLY
			|| tokenPrevious.type == DIVIDE
			|| tokenPrevious.type == LEFT_BRACKET)
			return true;
	}

	return false;
}

bool ExpressionTokeniser::UpdateCurrentOperand(char c)
{
	if (IsNumber(c))
	{
		if (operand.decimals == 0)
			operand.value = operand.value * 10 + toNumber(c);
		else
		{
			operand.value += pow(0.1, operand.decimals) * toNumber(c);

			// increase the decimal place
			operand.decimals++;
		}

		operand.traversingNumber = true;
	}
	else if (IsDecimal(c))
	{
		operand.decimals++;

		operand.traversingNumber = true;
	}
	else
	{
		// it's been an operand in the string so far
		if (operand.traversingNumber)
		{
			// collect the operand
			CollectOperand();

			operand.traversingNumber = false;
		}
	}

	return operand.traversingNumber;
}

void ExpressionTokeniser::CollectOperand()
{
	if (!operand.traversingNumber)
		return;

	// add a new token
	ExpressionToken token;
	token.value = operand.value;

	AddToken(token);

	// clear the operand info for the next operand
	operand.clear();
}

bool ExpressionTokeniser::CollectUnaryOperator(char c)
{
	if (IsUnaryOperator(c))
	{
		// convert '+' to '1' and '*'
		// otherwise convert '-' to '-1' and '*'
		ExpressionToken token;
		token.type = NUMBER;
		token.value = (c == '+') ? 1.0 : -1.0;

		AddToken(token);

		token.type = MULTIPLY;
		token.value = 0.0;

		AddToken(token);

		return true;
	}

	return false;
}

bool ExpressionTokeniser::CollectOperator(char c)
{
	if (!IsOperator(c))
		return false;

	// add the new token
	ExpressionToken token;
	switch (c)
	{
	case '+':
		token.type = ADD;
		break;
	case '-':
		token.type = SUBTRACT;
		break;
	case '*':
		token.type = MULTIPLY;
		break;
	case '/':
		token.type = DIVIDE;
		break;
	default:
		return false;
		break;
	}
	token.str = string(1, c);

	// add it to the list
	AddToken(token);

	return true;
}

bool ExpressionTokeniser::CollectBracket(char c)
{
	bool bLeftBracket(IsLeftBracket(c));
	bool bRightBracket(IsRightBracket(c));

	if (bLeftBracket || bRightBracket)
	{
		ExpressionToken token;
		if (bLeftBracket)
			token.type = LEFT_BRACKET;
		else
			token.type = RIGHT_BRACKET;

		token.str = string(1, c);

		// add it to the token line
		AddToken(token);

		return true;
	}

	return false;
}