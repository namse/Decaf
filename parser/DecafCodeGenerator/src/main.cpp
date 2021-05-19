#include "Decaf.h"
#include <fstream>
#include <string>
#include <iostream>

// Demonstrate some basic assertions.
int main()
{
  std::string decafFileString = R"CODE(
function Main(): Void {
}
)CODE";

  Decaf::Decaf decaf;

  auto result = decaf.ConvertToLLVM(decafFileString);
  std::cout << result << std::endl;

  std::string expected = R"CODE(

)CODE";

  return 0;
}
