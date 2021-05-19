#include "Lexer.h"
#include "Exceptions.h"

namespace Decaf
{
    std::tuple<TokenType, std::string> Lexer::GetNextToken()
    {
        auto lastChar = GetLastChar();
        while (isspace(lastChar))
        {
            lastChar = GetNextChar();
        }

        if (isupper(lastChar))
        {
            std::string tokenString;
            tokenString += lastChar;

            while (isalnum((lastChar = GetNextChar())))
            {
                tokenString += lastChar;
            }

            return std::make_pair(TokenType::PascalCaseIdentifier, tokenString);
        }

        if (isalnum(lastChar))
        {
            std::string tokenString;
            tokenString += lastChar;

            while (isalnum((lastChar = GetNextChar())))
            {
                tokenString += lastChar;
            }

            if (tokenString == FunctionToken::keyword)
            {
                return std::make_pair(TokenType::Function, tokenString);
            }
            if (tokenString == VarToken::keyword)
            {
                return std::make_pair(TokenType::Var, tokenString);
            }
            if (tokenString == ForToken::keyword)
            {
                return std::make_pair(TokenType::For, tokenString);
            }
            if (tokenString == DoToken::keyword)
            {
                return std::make_pair(TokenType::Do, tokenString);
            }
            if (tokenString == WhileToken::keyword)
            {
                return std::make_pair(TokenType::While, tokenString);
            }
            if (tokenString == InToken::keyword)
            {
                return std::make_pair(TokenType::In, tokenString);
            }

            return std::make_pair(TokenType::CamelCaseIdentifier, tokenString);
        }

        GetNextChar();
        return std::make_pair(TokenType::Unknown, std::string(1, lastChar));
    }

    std::unique_ptr<FunctionToken> Lexer::ConsumeFunctionToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::Function)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<FunctionToken>(string);
    }

    std::unique_ptr<VarToken> Lexer::ConsumeVarToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::Var)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<VarToken>(string);
    }

    std::unique_ptr<ForToken> Lexer::ConsumeForToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::For)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<ForToken>(string);
    }

    std::unique_ptr<DoToken> Lexer::ConsumeDoToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::Do)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<DoToken>(string);
    }

    std::unique_ptr<WhileToken> Lexer::ConsumeWhileToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::While)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<WhileToken>(string);
    }

    std::unique_ptr<InToken> Lexer::ConsumeInToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::In)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<InToken>(string);
    }

    std::unique_ptr<CamelCaseIdentifierToken> Lexer::ConsumeCamelCaseIdentifierToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::CamelCaseIdentifier)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<CamelCaseIdentifierToken>(string);
    }

    std::unique_ptr<PascalCaseIdentifierToken> Lexer::ConsumePascalCaseIdentifierToken()
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::PascalCaseIdentifier)
        {
            throw UnexpectedTokenException(tokenType, string);
        }

        return std::make_unique<PascalCaseIdentifierToken>(string);
    }

    void Lexer::ConsumeSingleCharacter(char character)
    {
        const auto [tokenType, string] = GetNextToken();
        if (tokenType != TokenType::Unknown || string.length() > 1 || string.at(0) != character)
        {
            throw UnexpectedTokenException(tokenType, string);
        }
    }

    char Lexer::GetNextChar()
    {
        if (IsEnd())
        {
            return code[code.length() - 1];
        }

        return code[++codeIndex];
    }

    bool Lexer::IsEnd()
    {
        return code.length() <= codeIndex;
    }

    char Lexer::GetLastChar()
    {
        return code[codeIndex];
    }

}