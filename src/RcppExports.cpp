// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// tokenize_
List tokenize_(CharacterVector formula);
RcppExport SEXP xlformula_tokenize_(SEXP formulaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type formula(formulaSEXP);
    rcpp_result_gen = Rcpp::wrap(tokenize_(formula));
    return rcpp_result_gen;
END_RCPP
}
