#include <string>
#include "parser.tab.hh"

#define YY_DECL \
  yy::Parser::symbol_type yylex (Driver& driver)
YY_DECL;

class Driver {
  public:
    void runScannerFile();
    void closeFile();
    void parseFile(const std::string& archivo);
    void parse(const std::string texto);
    void runScanner(std:: string texto);
    std::string file;
};