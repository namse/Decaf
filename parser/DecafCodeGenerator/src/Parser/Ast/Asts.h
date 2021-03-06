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
            std::shared_ptr<PascalCaseIdentifierToken> functionNameToken,
            std::shared_ptr<PascalCaseIdentifierToken> functionReturnTypeToken,
            std::shared_ptr<BlockAst> blockAst)
            : Ast(AstType::Function),
              functionNameToken(std::move(functionNameToken)),
              functionReturnTypeToken(std::move(functionReturnTypeToken)),
              blockAst(std::move(blockAst))
        {
        }

    public:
        const std::shared_ptr<PascalCaseIdentifierToken> functionNameToken;
        const std::shared_ptr<PascalCaseIdentifierToken> functionReturnTypeToken;
        const std::shared_ptr<BlockAst> blockAst;
    };

}
