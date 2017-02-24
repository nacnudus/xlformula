#include "Token.h"

namespace ExcelFormula
{

	Token::Token():
		m_value(),
		m_type(Unknown),
		m_subtype(Nothing){}

	Token::Token(const char* szValue, TokenType type):
	m_value(szValue),
	m_type(type),
	m_subtype(Nothing) {}

	Token::Token(const char* szValue, TokenType type, TokenSubtype subtype):
		m_value(szValue),
		m_type(type),
		m_subtype(subtype) {}

	bool Token::operator==(Token& token) {
		if (token.getType() == getType()
				&& token.getSubtype() == getSubtype()
				&& token.getStrValue().compare(getStrValue()) == 0)
			return true;
		else
			return false;
	}

	const string Token::getTokenType()
  {
		switch(m_type)
		{
			case Operand:
				return "operand";
				break;
			case Function:
				return "function";
				break;
			case Subexpression:
				return "subexpression";
				break;
			case Argument:
				return "argument";
				break;
			case OperatorPrefix:
				return "operator prefix";
				break;
			case OperatorInfix:
				return "operator infix";
				break;
			case OperatorPostfix:
				return "operator postfix";
				break;
			case Whitespace:
				return "whitespace";
				break;
			case Unknown:
				return "unknown";
				break;
		}//token type switch
	} //func  getTokenType

	const string Token::getTokenSubtype()
  {
		switch(m_subtype)
		{
			case Nothing:
				return "nothing";
				break;
			case Start:
				return "start";
				break;
			case Stop:
				return "stop";
				break;
			case Text:
				return "text";
				break;
			case Number:
				return "number";
				break;
			case Logical:
				return "logical";
				break;
			case Error:
				return "error";
				break;
			case Path:
				return "path";
				break;
			case Range:
				return "range";
				break;
			case Math:
				return "math";
				break;
			case Concatenation:
				return "concatenation";
				break;
			case Intersection:
				return "intersection";
				break;
			case Union:
				return "union";
				break;
		}//token subtype switch
	} //func  getTokenSubtype

	Token* Token::clone()
	{
		return TokenAllocer::getToken(getValue(), getType(), getSubtype());
	}

	Token* TokenAllocer::getToken()
	{
		return new Token();
	}

	Token* TokenAllocer::getToken(const char* szValue, Token::TokenType type)
	{
		return new Token(szValue, type);
	}

	Token* TokenAllocer::getToken(const char* szValue, Token::TokenType type,
			Token::TokenSubtype subtype)
	{
		return new Token(szValue, type, subtype);
	}

	void TokenAllocer::freeToken(Token* pToken)
	{
		delete pToken;
	}

}//namespace









