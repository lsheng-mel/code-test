#pragma once

//! base class for compiling collected tokens from a given expression string
//! this is made to be an interface for easy functionality extension in the future
class ExpressionTokensCompilerBase
{
public:
	ExpressionTokensCompilerBase(){}

public:
	void virtual Compile() = 0;
};
