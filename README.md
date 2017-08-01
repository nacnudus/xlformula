# xlformula

An experimental R package for parsing (really just tokenising) Excel formulas in
R, based on my [fork](https://github.com/nacnudus/Excel_formula_parser_cpp) of a
[C++ port](https://github.com/lishen2/Excel_formula_parser_cpp) of a basic,
handwritten javascript
[parser](http://ewbi.blogs.com/develops/2004/12/excel_formula_p.html).  The end
goal is to de-normalise shared formulas in tidyxl, where there is an
[issue](https://github.com/nacnudus/tidyxl/issues/7) that explains all this much
better.
