Rcpp::compileAttributes()
clean_dll()
document()
install()

library(xlformula)
tokenize("=A1")

xlformula:::tokenize_("=DeptSales[@Commission Amount]") # TODO:
xlformula:::tokenize_("=SUM(Table1[col1],Table1[@col2],4)")
xlformula:::tokenize_("=SUM(Table1[col1],Table1[[#Headers],[col2]],4)")
xlformula:::tokenize_("=IF(R13C3>DATE(2002,1,6),0,IF(ISERROR(R41C[2]),0,IF(R13C3>=R[2]C2:R[6]C[3],0, IF(AND(R[23]C11>=55,R[24]C[11]>=20),R53C3,0))))")

xlformula:::tokenize_("=\"Hello, \"\"World\"\"\"&\"I can see you\"")
xlformula:::tokenize_("='C:\\users\\My Documents\\[border.xlsx]Sheet1'!$A$1")
xlformula:::tokenize_("=ABCD")

# TODO: remove support for R!C!, which is never written to file (ECMA part 1 p.
# 2055)

# TODO: regex for formulas vs names
# ^(R\[?[0-9]?\]?C\[?[0-9]?\]?)(:R\[?[0-9]?\]?C\[?[0-9]?\]?)?$ # RC is not a valid name, fortunately
# ^(\$?[A-Z]*\$?[1-9]*)(:\$?[A-Z]*\$?[1-9]*)?$
xlformula:::tokenize_("=A1B2")         # Name, not formula

xlformula:::tokenize_("=A1")
xlformula:::tokenize_("=$A1")
xlformula:::tokenize_("=A$1")
xlformula:::tokenize_("=$A$1")

xlformula:::tokenize_("=A:B")
xlformula:::tokenize_("=$A:B")
xlformula:::tokenize_("=A:$B")
xlformula:::tokenize_("=$A:$B")

xlformula:::tokenize_("=1:2")
xlformula:::tokenize_("=$1:2")
xlformula:::tokenize_("=1:$2")
xlformula:::tokenize_("=$1:$2")

xlformula:::tokenize_("=A1:B2")
xlformula:::tokenize_("=$A1:B2")
xlformula:::tokenize_("=A$1:B2")
xlformula:::tokenize_("=A1:$B2")
xlformula:::tokenize_("=A1:B$2")
xlformula:::tokenize_("=$A$1:B2")
xlformula:::tokenize_("=$A1:$B2")
xlformula:::tokenize_("=$A1:B$2")
xlformula:::tokenize_("=A$1:$B2")
xlformula:::tokenize_("=A$1:B$2")
xlformula:::tokenize_("=A1:$B$2")
xlformula:::tokenize_("=$A$1:$B2")
xlformula:::tokenize_("=$A$1:B$2")
xlformula:::tokenize_("=$A1:$B$2")
xlformula:::tokenize_("=A$1:$B$2")
xlformula:::tokenize_("=$A$1:$B$2")

xlformula:::tokenize_("={1,2;3,4}")
xlformula:::tokenize_("=SUM(C1:C11 A5:F6)")
xlformula:::tokenize_("=INDEX(C:C,MATCH($A$1,$B:$B,0))")
xlformula:::tokenize_("=Sheet2!A2")
xlformula:::tokenize_("=SUM(Sheet1:Sheet3!C2)")

xlformula:::tokenize_("=CONCATENATE(\"Hello\",\"World!\",SUM(1,$A1:B$2,Table1[@col2]))")


xlformula:::tokenize_("=IF(\"a\"={\"a\",\"b\";\"c\",#N/A;-1,TRUE}, \"yes\", \"no\") &   \"  more \"\"test\"\" text\"")
xlformula:::tokenize_("=+ AName- (-+-+-2^6) = {\"A\",\"B\"} + @SUM(R1C1) + (@ERROR.TYPE(#VALUE!) = 2)")
xlformula:::tokenize_("=IF(R13C3>DATE(2002,1,6),0,IF(ISERROR(R[41]C[2]),0,IF(R13C3>=R[41]C[2],0, IF(AND(R[23]C[11]>=55,R[24]C[11]>=20),R53C3,0))))")
xlformula:::tokenize_("=IF(R[39]C[11]>65,R[25]C[42],ROUND((R[11]C[11]*IF(OR(AND(R[39]C[11]>=55, R[40]C[11]>=20),AND(R[40]C[11]>=20,R11C3=\"YES\")),R[44]C[11],R[43]C[11]))+(R[14]C[11] *IF(OR(AND(R[39]C[11]>=55,R[40]C[11]>=20),AND(R[40]C[11]>=20,R11C3=\"YES\")), R[45]C[11],R[43]C[11])),0))")

library(Rcpp)
cppFunction(
  "CharacterVector num2col(int num) {
    int dividend = num;
    int modulo;
    char letter;
    std::string col;
    while (dividend > 0) {
      modulo = (dividend - 1) % 26;
      letter = 'A' + modulo;
      col = letter + col;
      dividend = (dividend - modulo) / 26;
    }
    return col;
  }",
  plugins=c("cpp11"))
num2col(27)

library(Rcpp)
cppFunction(
  "IntegerVector col2num(std::string col) {
    int num = 0;
    for(std::string::const_iterator iter = col.begin();
        iter != col.end();
        ++iter) {
      num = 26 * num + (*iter - 'A' + 1);
    }
    IntegerVector out(1, num);
    return out;
  }",
  plugins=c("cpp11"))
col2num("AA")


# library(Rcpp)
# cppFunction(
#   'IntegerVector foo(CharacterVector x) {
#     std::string xstring = Rcpp::as<std::string>(x);
#     const char * xchar = xstring.c_str();
#     const char *rx= "^R[1-9]";
#     const char *error;
#     int erroffset;
#     pcre *m_rx;
#     m_rx= pcre_compile(rx,
#       0,
#       &error,
#       &erroffset,
#       0);
#     int rc;
#     unsigned int offset = 0;
#     int ovector[100];
#     rc = pcre_exec(m_rx, 0, xchar, 2, offset, 0, ovector, sizeof(ovector));
#     IntegerVector out(1, rc);
#     return out;
#   }',
#    includes = '#include "pcre.h"')
# foo("Az")
# foo("R1")
