#include "CodeGenerator.h"
#include <fstream>
#include <string>

// Demonstrate some basic assertions.
int main()
{
  std::string decafFileString = R"CODE(
function Main(): Void {
}
)CODE";

  Decaf::CodeGenerator codeGenerator;

  auto result = codeGenerator.ConvertToLLVM(decafFileString);

  std::string expected = R"CODE(

)CODE";

  return 0;
}
