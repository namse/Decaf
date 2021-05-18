#include <gtest/gtest.h>
#include "src/CodeGenerator.h"
#include <fstream>

// Demonstrate some basic assertions.
TEST(HelloTest, SimpleMainFunciton)
{
  std::string decafFileString = R"CODE(
function Main(): Void {
}
)CODE";

  Decaf::CodeGenerator codeGenerator;

  auto result = codeGenerator.ConvertToLLVM(decafFileString);

  std::string expected = R"CODE(

)CODE";

  EXPECT_TRUE(expected == result);
}
