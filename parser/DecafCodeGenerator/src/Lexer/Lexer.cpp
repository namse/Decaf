#include "Lexer.h";

namespace Decaf
{
    Lexer::Lexer(std::string code)
        : _code(code)
    {
    }

    Token Lexer::GetNextToken()
    {
        auto lastChar = GetNextChar();
        while (isspace(lastChar))
        {
            lastChar = GetNextChar();
        }

        if (isupper(lastChar))
        {
            std::string tokenString;
            tokenString += lastChar;

            while (isalnum((lastChar = GetNextChar())))
                tokenString += lastChar;

            return PascalCaseIdentifierToken(tokenString);
        }

        return Token::EofToken;
    }
}