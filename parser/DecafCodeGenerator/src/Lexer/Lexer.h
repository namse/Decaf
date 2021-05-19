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
        std::unique_ptr<FunctionToken> ConsumeFunctionToken();
        std::unique_ptr<VarToken> ConsumeVarToken();
        std::unique_ptr<ForToken> ConsumeForToken();
        std::unique_ptr<DoToken> ConsumeDoToken();
        std::unique_ptr<WhileToken> ConsumeWhileToken();
        std::unique_ptr<InToken> ConsumeInToken();
        std::unique_ptr<CamelCaseIdentifierToken> ConsumeCamelCaseIdentifierToken();
        std::unique_ptr<PascalCaseIdentifierToken> ConsumePascalCaseIdentifierToken();
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
