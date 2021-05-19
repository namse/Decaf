#include "Parser.h"

namespace Decaf
{

    std::vector<std::unique_ptr<Ast>> Parser::Parse(Lexer &lexer)
    {
        std::vector<std::unique_ptr<Ast>> asts;
        try
        {
            while (!lexer.IsEnd())
            {
                auto functionAst = ParseFunctionAst(lexer);
                asts.push_back(std::move(functionAst));
            }
        }
        catch (std::exception exception)
        {
        }

        return asts;
    }

    std::unique_ptr<FunctionAst> Parser::ParseFunctionAst(Lexer &lexer)
    {
        lexer.ConsumeFunctionToken();

        auto functionNameToken = lexer.ConsumePascalCaseIdentifierToken();

        lexer.ConsumeSingleCharacter('(');

        // TODO : function parameter list

        lexer.ConsumeSingleCharacter(')');
        
        lexer.ConsumeSingleCharacter(':');

        auto functionReturnTypeToken = lexer.ConsumePascalCaseIdentifierToken();

        auto blockAst = ParseBlockAst(lexer);

        return std::make_unique<FunctionAst>(
            std::move(functionNameToken),
            std::move(functionReturnTypeToken),
            std::move(blockAst));
    }

    std::unique_ptr<BlockAst> Parser::ParseBlockAst(Lexer &lexer)
    {
        lexer.ConsumeSingleCharacter('{');
        // TODO : statements
        lexer.ConsumeSingleCharacter('}');
        return std::make_unique<BlockAst>();
    }
}
