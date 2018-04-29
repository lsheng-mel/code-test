#pragma once
#include <string>
#include "ExpressionTokeniser.h"
#include "ExpressionTokensValidator.h"
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

	//! returns the validity of the evaluation
	bool IsEvaluationValid() { return bValid; }

private:
	//! do the final evaluation
	double DoEvaluation(const std::vector<ExpressionToken>& evaluationStack);

	//! set validity
	void SetValid(bool val) { bValid = val; }

private:
	bool bValid;

	std::string expression;

	ExpressionTokeniser tokeniser;
	ExpressionTokensValidator validator;
	ExpressionTokensCompiler compiler;
};
