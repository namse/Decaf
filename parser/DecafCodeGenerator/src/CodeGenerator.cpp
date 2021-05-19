#include "CodeGenerator.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

namespace Decaf {
    std::string CodeGenerator::ConvertToLLVM(std::string decafCode)
    {
        Lexer lexer(decafCode);
        Parser parser;
        parser.Parse(lexer);
        return "";
    }
}
