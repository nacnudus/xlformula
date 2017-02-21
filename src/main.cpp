#include "FormulaParser.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using ExcelFormula::Token;
using ExcelFormula::FormulaParser;

void printIndent(int i)
{
	for(int j = 0; j < i; ++j)
	{
		cout << "|";
	}
}


void printParser(FormulaParser& parser)
{
	vector<Token*> tokens = parser.getTokens();
	cout << "Formula:" << parser.getFormula() << endl;
	cout << "Tokens:" << endl;

	int indent = 0;
	for(vector<Token*>::iterator it = tokens.begin();
			it != tokens.end();
			++it)
	{
		if((*it)->getSubtype() == Token::Start)
		{
			++indent;
		}
		printIndent(indent);
		cout << (*it)->getPrintableString() << endl;
		if((*it)->getSubtype() == Token::Stop)
		{
			--indent;
		}
	}

	cout << endl;
}


int main(int argc, char* argv[])
{
	const char szFormula1[] = "=A1A1";
	FormulaParser parser1(szFormula1);
	parser1.parserToToken1();
	parser1.parserToToken2();
	printParser(parser1);

	const char szFormula2[] = "=__.?";
	FormulaParser parser2(szFormula2);
	parser2.parserToToken1();
	parser2.parserToToken2();
	printParser(parser2);

	const char szFormula3[] = "=[c:/blah/de/blah.xls]Sheet1!A1";
	FormulaParser parser3(szFormula3);
	parser3.parserToToken1();
	parser3.parserToToken2();
	printParser(parser3);

	const char szFormula4[] = "=50*10%";
	FormulaParser parser4(szFormula4);
	parser4.parserToToken1();
	parser4.parserToToken2();
	printParser(parser4);

	/* const char szFormula2[] = "=IF(R13C3>DATE(2002,1,6),0,IF(ISERROR(R[41]C[2]),0,IF(R13C3>=R[41]C[2],0, IF(AND(R[23]C[11]>=55,R[24]C[11]>=20),R53C3,0))))"; */
	/* FormulaParser parser2(szFormula2); */
	/* parser2.parserToToken1(); */
	/* parser2.parserToToken2(); */
	/* printParser(parser2); */

	return 0;
}
