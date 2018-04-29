#pragma once
#include <string>
#include "ExpressionTokeniser.h"
#include "ExpressionTokensCompiler.h"
#include "ExpressionToken.h"

class ExpressionEvaluator
{
public:
	ExpressionEvaluator();

public:
	//! evaluate the expression that was given
	double Evaluate();

	//! set up the expression
	void SetExpression(const std::string expression);

private:
	//! do the final evaluation
	double DoEvaluation(std::vector<ExpressionToken>& evaluationStack);

private:
	std::string expression;

	ExpressionTokeniser tokeniser;
	ExpressionTokensCompiler compiler;
};
