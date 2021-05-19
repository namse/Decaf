#pragma once
#include <memory>
#include "Lexer/Token/Tokens.h"

namespace Decaf
{
    struct UnexpectedTokenException : public std::exception
    {
        UnexpectedTokenException(TokenType tokenType, std::string string)
            : tokenType(tokenType),
              string(string)
        {
        }

        const TokenType tokenType;
        const std::string string;
    };

    struct UnexpectedCharacterException : public std::exception
    {
        UnexpectedCharacterException(char chatacter, TokenType tokenType)
            : chatacter(chatacter),
              tokenType(tokenType)
        {
        }

        const char chatacter;
        const TokenType tokenType;
    };
}
