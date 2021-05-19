#pragma once
#include "Ast/Asts.h"
#include "../Lexer/Lexer.h"
#include <vector>
#include <exception>
#include <memory>

namespace Decaf
{
    class Parser
    {
    public:
        std::vector<std::unique_ptr<Ast>> Parse(Lexer &lexer);

    private:
        std::unique_ptr<FunctionAst> ParseFunctionAst(Lexer &lexer);
        std::unique_ptr<BlockAst> ParseBlockAst(Lexer &lexer);
    };

}
