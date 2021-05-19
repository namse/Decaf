#include <gtest/gtest.h>
#include "Decaf.h"
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

  Decaf::Decaf decaf;

  auto result = decaf.ConvertToLLVM(decafFileString);

  std::string expected = R"CODE(

)CODE";

  EXPECT_TRUE(expected == result);
}
