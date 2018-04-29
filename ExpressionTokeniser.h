#pragma once
#include <string>
#include <vector>
#include "ExpressionToken.h"

// used for tracking a number going across a continous list of characters within an expression
struct numberTraverse
{
	//! are we currently traversing a number through the expression
	bool traversingNumber;

	//! the value of the operand
	double value;

	//! the decimal number
	int decimals;

	//! constructor
	numberTraverse()
	{
		clear();
	}

	//! reset the traverse
	void clear() {
		traversingNumber = false;
		value = 0.0;
		decimals = 0;
	}
};

class ExpressionTokeniser
{
public:
	ExpressionTokeniser();

public:
	// operations

	//! tokenise the given string
	//! returns false if unexpected characters found
	bool Tokenise(std::string expression);

	//! get the collected tokens
	std::vector<ExpressionToken>& GetTokens() { return vecTokens; }

private:
	int toNumber(char c);
	bool IsNumber(char c);
	bool IsDecimal(char c);
	bool IsLeftBracket(char c);
	bool IsRightBracket(char c);
	bool IsBracket(char c);
	bool IsOperator(char c);

	//! update the current operand info based on the current character
	//! --- 
	//! returns true if it is operand related, otherwise false
	//! ---
	bool UpdateCurrentOperand(char c);

	//! collect the current operand
	void CollectOperand();

	//! collect an operator
	//! returns true if it is an operator
	bool CollectOperator(char c);

	//! collect a bracket
	//! returns truss if it is a bracket
	bool CollectBracket(char c);

	//! add an operand token into the list
	void AddToken(ExpressionToken token) { vecTokens.push_back(token); }

	//! clear all tokens from the list
	void ClearTokens() { vecTokens.clear(); }

private:
	//! current operand
	numberTraverse operand;

	//! the list of collected operands
	std::vector<ExpressionToken> vecTokens;
};
