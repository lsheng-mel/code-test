#pragma once
#include <vector>
#include "ExpressionTokensCompilerBase.h"
#include "ExpressionToken.h"

class ExpressionTokensCompiler : public ExpressionTokensCompilerBase
{
public:
	ExpressionTokensCompiler();

public:
	// operations

	//! compile the tokens based on given data
	void virtual Compile();

	//! set the list of tokens
	void SetTokens(const std::vector<ExpressionToken>& tokens) { vecTokens = tokens; }

	//! retrieve the finalised evaluation stack
	const std::vector<ExpressionToken>& GetEvaluationStack() { return vecOperands; }

private:
	void AddOperand(ExpressionToken item) { vecOperands.push_back(item); }
	void AddOperator(ExpressionToken item) { vecOperators.push_back(item); }

	//! returns true if the given operator has the highest precedence compared to all existing operators in the stack
	//! otherwise returns the operators have higher precedence
	bool CheckOperatorOfPrecedence(const ExpressionToken& token, bool bAdjustTokens=true);

	//! create the stack used for final evaluation
	void MakeFinalEvaluationStack();

	//! clear all data
	void Clear() { vecOperands.clear(); vecOperators.clear(); }

private:
	//! given tokens
	std::vector<ExpressionToken> vecTokens;

	//! operands
	std::vector<ExpressionToken> vecOperands;

	//! operators
	std::vector<ExpressionToken> vecOperators;
};
