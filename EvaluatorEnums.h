#pragma once

//! this enum defines varies types of mathmatical tokens
enum ExpressionTokenType
{
	NUMBER,			// numbers, including floating numbers
	ADD,			// "+"
	SUBTRACT,		// "-"
	MULTIPLY,		// "*"
	DIVIDE,			// "/"
	POWER,			// "^"
	LEFT_BRACKET,	// "("
	RIGHT_BRACKET	// ")"
};
