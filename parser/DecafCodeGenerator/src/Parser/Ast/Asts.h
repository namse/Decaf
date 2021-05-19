#pragma once
#include "Lexer/Token/Tokens.h"
#include <memory>

namespace Decaf
{
    enum class AstType
    {
        Function,
        Block,
    };

    class Ast
    {
    public:
        virtual ~Ast() = default;

    protected:
        Ast(AstType astType)
            : astType(astType)
        {
        }

    public:
        const AstType astType;
    };

    class BlockAst : public Ast
    {
    public:
        BlockAst()
            : Ast(AstType::Block)
        {
        }

    private:
    };

    class FunctionAst : public Ast
    {
    public:
        FunctionAst(
            std::unique_ptr<PascalCaseIdentifierToken> functionNameToken,
            std::unique_ptr<PascalCaseIdentifierToken> functionReturnTypeToken,
            std::unique_ptr<BlockAst> blockAst)
            : Ast(AstType::Function),
              functionNameToken(std::move(functionNameToken)),
              functionReturnTypeToken(std::move(functionReturnTypeToken)),
              blockAst(std::move(blockAst))
        {
        }

    private:
        const std::unique_ptr<PascalCaseIdentifierToken> functionNameToken;
        const std::unique_ptr<PascalCaseIdentifierToken> functionReturnTypeToken;
        const std::unique_ptr<BlockAst> blockAst;
    };

}
