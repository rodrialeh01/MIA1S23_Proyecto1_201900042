#include "driver.h"
#include "parser.tab.hh"

void Driver::parseFile(const std::string& archivo){
  file = archivo;

  runScannerFile();
  yy::Parser parser(*this);
  parser.set_debug_level(false);
  parser.parse();
  closeFile();
}

void Driver::parse(std::string texto){
  runScanner(texto);
  yy::Parser parser(*this);
  parser.set_debug_level(false);
  parser.parse();
}