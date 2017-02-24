#include "FormulaParser.h"
#include <Rcpp.h>

using ExcelFormula::Token;
using ExcelFormula::FormulaParser;

using namespace Rcpp;

// [[Rcpp::export()]]
List foo2(CharacterVector formula) {
  std::string formula_string = Rcpp::as<std::string>(formula);
	const char * szFormula1 = formula_string.c_str();
	FormulaParser parser1(szFormula1);

  std::vector<std::string> tokens_vec;
  std::vector<int>         levels_vec;

	vector<Token*> tokens = parser1.getTokens();
	int level = 0;
	for(vector<Token*>::iterator it = tokens.begin();
			it != tokens.end();
			++it)
	{
		if((*it)->getSubtype() == Token::Start)
		{
			++level;
		}
    tokens_vec.push_back((*it)->getPrintableString());
    levels_vec.push_back(level);
		if((*it)->getSubtype() == Token::Stop)
		{
			--level;
		}
	}

  CharacterVector tokens_out(tokens_vec.begin(), tokens_vec.end());
  NumericVector levels_out(levels_vec.begin(), levels_vec.end());

  List out = List::create(
      _["level"] = levels_out,
      _["token"] = tokens_out);

  int n = Rf_length(out[0]);
  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -n);

  return out;
}
