#pragma once
#include <string>
#include <memory>
#include <tuple>
#include "Token/Tokens.h"

namespace Decaf
{
    class Lexer
    {

    public:
        Lexer(std::string code)
            : code(code)
        {
        }
        std::shared_ptr<FunctionToken> ConsumeFunctionToken();
        std::shared_ptr<VarToken> ConsumeVarToken();
        std::shared_ptr<ForToken> ConsumeForToken();
        std::shared_ptr<DoToken> ConsumeDoToken();
        std::shared_ptr<WhileToken> ConsumeWhileToken();
        std::shared_ptr<InToken> ConsumeInToken();
        std::shared_ptr<CamelCaseIdentifierToken> ConsumeCamelCaseIdentifierToken();
        std::shared_ptr<PascalCaseIdentifierToken> ConsumePascalCaseIdentifierToken();
        void ConsumeSingleCharacter(char character);
        bool IsEnd();

    private:
        std::tuple<TokenType, std::string> GetNextToken();
        char GetNextChar();
        char GetLastChar();

    private:
        std::string code;
        int codeIndex = 0;
    };
}
