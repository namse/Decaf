#include "Decaf.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/CodeGenerator/CodeGenerator.h"

namespace Decaf
{
    std::string Decaf::ConvertToLlvm(llvm::Module& module, std::string decafCode)
    {
        LoadToLlvmModule(module, decafCode);

        std::string llvmCode;
        llvm::raw_string_ostream ostream(llvmCode);
        ostream << module;
        ostream.flush();
        return llvmCode;
    }

    void Decaf::LoadToLlvmModule(llvm::Module& module, std::string decafCode)
    {
        Lexer lexer(decafCode);
        Parser parser;
        CodeGenerator codeGenerator(&module);
        auto asts = parser.Parse(lexer);

        for (const auto &ast : asts)
        {
            if (ast->astType == AstType::Function)
            {
                auto functionAst = std::static_pointer_cast<FunctionAst>(ast);
                codeGenerator.GenerateFunctionCode(functionAst);
            }
        }
    }
}
