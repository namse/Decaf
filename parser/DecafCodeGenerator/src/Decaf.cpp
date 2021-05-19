#include "Decaf.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/CodeGenerator/CodeGenerator.h"

namespace Decaf
{
    std::string Decaf::ConvertToLLVM(std::string decafCode)
    {
        Lexer lexer(decafCode);
        Parser parser;
        CodeGenerator codeGenerator;
        auto asts = parser.Parse(lexer);

        for (const auto &ast : asts)
        {
            if (ast->astType == AstType::Function) {
                auto functionAst = std::static_pointer_cast<FunctionAst>(ast);
                codeGenerator.GenerateFunctionCode(functionAst);
            }
        }

        return codeGenerator.DumpAllCode();
    }
}
