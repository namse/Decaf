#pragma once
#include <string>

namespace Decaf
{
    enum class TokenType
    {
        Unknown = -1,

        // Keywords
        Function,
        Var,
        For,
        Do,
        While,
        In,

        CamelCaseIdentifier,
        PascalCaseIdentifier,
    };

    class Token
    {
        
    public:
        virtual ~Token() = default;
        // public:
        //     Token(Token &&) = default;
        //     Token(const Token &) = default;
        Token &operator=(const Token &_)
        {
            return *this;
        }

    protected:
        Token(std::string string, TokenType tokenType)
            : string(string),
              tokenType(tokenType)
        {
        }

    public:
        const std::string string;
        const TokenType tokenType;
    };

    class UnknownToken : public Token
    {
    public:
        UnknownToken(std::string string)
            : Token(string, TokenType::Unknown)
        {
        }
    };

    class FunctionToken : public Token
    {
    public:
        FunctionToken(std::string string)
            : Token(string, TokenType::Function)
        {
        }
        const static std::string keyword;
    };

    class VarToken : public Token
    {
    public:
        VarToken(std::string string)
            : Token(string, TokenType::Var)
        {
        }
        const static std::string keyword;
    };

    class ForToken : public Token
    {
    public:
        ForToken(std::string string)
            : Token(string, TokenType::For)
        {
        }
        const static std::string keyword;
    };

    class DoToken : public Token
    {
    public:
        DoToken(std::string string)
            : Token(string, TokenType::Do)
        {
        }
        const static std::string keyword;
    };

    class WhileToken : public Token
    {
    public:
        WhileToken(std::string string)
            : Token(string, TokenType::While)
        {
        }
        const static std::string keyword;
    };

    class InToken : public Token
    {
    public:
        InToken(std::string string)
            : Token(string, TokenType::In)
        {
        }
        const static std::string keyword;
    };

    class CamelCaseIdentifierToken : public Token
    {
    public:
        CamelCaseIdentifierToken(std::string string)
            : Token(string, TokenType::CamelCaseIdentifier)
        {
        }
    };

    class PascalCaseIdentifierToken : public Token
    {
    public:
        PascalCaseIdentifierToken(std::string string)
            : Token(string, TokenType::PascalCaseIdentifier)
        {
        }
    };

}
