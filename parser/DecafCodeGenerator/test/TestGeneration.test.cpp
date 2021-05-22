#include <gtest/gtest.h>
#include "Decaf.h"
#include <fstream>
#include <string>

// Demonstrate some basic assertions.
TEST(HelloTest, SimpleMainFunciton)
{
    std::string decafFileString = R"CODE(
function Main(): Void {
}
)CODE";

    Decaf::Decaf decaf;

    llvm::LLVMContext context;
    llvm::Module module("Decaf", context);
    auto result = decaf.ConvertToLlvm(module, decafFileString);

    std::string expected = R"CODE(; ModuleID = 'Decaf'
source_filename = "Decaf"

define void @Main() {
entry:
  ret void
}
)CODE";

    EXPECT_EQ(expected, result);
}
