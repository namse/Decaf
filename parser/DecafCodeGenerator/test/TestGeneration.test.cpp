#include <gtest/gtest.h>
#include "CodeGenerator.h"
#include <fstream>
#include <string>

// Demonstrate some basic assertions.
TEST(HelloTest, SimpleMainFunciton)
{
    EXPECT_TRUE(true);
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
