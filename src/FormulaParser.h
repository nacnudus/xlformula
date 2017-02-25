#include "Token.h"
#include "TokenArray.h"
#include "TokenStack.h"
#include "pcre.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace ExcelFormula
{
	class TokenArray;
	class TokenStack;

	class FormulaParser
	{
		public:
			FormulaParser(const char* szFormula);

			const char* getFormula(){return m_formula.c_str();}

			size_t getSize(){return m_tokens.size();}

			vector<Token*>& getTokens()
			{
				return m_tokens;
			}

			/**
			 * clear internal token array,
			 * and release the monery
			 */
			void clear();

		private:
			FormulaParser();

			string m_formula;

			vector<Token*> m_tokens;

			TokenArray m_tmpAry;

			TokenStack m_tmpStack;

			pcre *m_rx_scientific;
			pcre *m_rx_r1c1;

			/** scan formula and translate it
			 * into tokens literally
			 */
			void parserToToken1();

			/**
			 * do some magic to he token array
			 * inorder to correct the function ending
			 * and remove some empty space token
			 *
			 * @param TokenArray* tmpToken form parserToToken1
			 * @param TokenArray* the final token array
			 */
			void parserToToken2();

	}; //class ExcelFormula


} //namespace

