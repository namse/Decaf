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
        std::vector<std::shared_ptr<Ast>> Parse(Lexer &lexer);

    private:
        std::shared_ptr<FunctionAst> ParseFunctionAst(Lexer &lexer);
        std::shared_ptr<BlockAst> ParseBlockAst(Lexer &lexer);
    };

}
