#include "FormulaParser.h"
#include <Rcpp.h>

using ExcelFormula::Token;
using ExcelFormula::FormulaParser;

using namespace Rcpp;

// [[Rcpp::export()]]
List tokenize_(CharacterVector formula) {
  std::string formula_string = Rcpp::as<std::string>(formula);
	const char * szFormula1 = formula_string.c_str();
	FormulaParser parser(szFormula1);

  std::vector<std::string> literal;
  std::vector<std::string> token;
  std::vector<std::string> type;
  std::vector<std::string> subtype;
  std::vector<int>         level;

	vector<Token*> tokens = parser.getTokens();
	int depth = 0;
	for(vector<Token*>::iterator it = tokens.begin();
			it != tokens.end();
			++it)
	{
		if((*it)->getSubtype() == Token::Start)
		{
			++depth;
		}
    literal.push_back((*it)->getTokenLiteral());
    token.push_back((*it)->getTokenValue());
    type.push_back((*it)->getTokenType());
    subtype.push_back((*it)->getTokenSubtype());
    level.push_back(depth);
		if((*it)->getSubtype() == Token::Stop)
		{
			--depth;
		}
	}

  CharacterVector literal_out(literal.begin(), literal.end());
  CharacterVector token_out(token.begin(), token.end());
  CharacterVector type_out(type.begin(), type.end());
  CharacterVector subtype_out(subtype.begin(), subtype.end());
  NumericVector level_out(level.begin(), level.end());

  List out = List::create(
      _["level"] = level,
      _["literal"] = literal_out,
      _["token"] = token_out,
      _["type"] = type_out,
      _["subtype"] = subtype_out);

  int n = Rf_length(out[0]);
  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -n);

  return out;
}
