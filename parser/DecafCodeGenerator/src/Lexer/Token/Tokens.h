#include <string>

namespace Decaf
{
    enum class TokenType
    {
        Eof = -1,

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
            static const Token EofToken;

        protected:
            Token(std::string string)
            : String(string)
            {}
        public:
            const std::string String;
    };

    class FunctionToken : public Token
    {
    public:
        FunctionToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::Function;
    };

    class VarToken : public Token
    {
    public:
        VarToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::Var;
    };

    class ForToken : public Token
    {
    public:
        ForToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::For;
    };

    class DoToken : public Token
    {
    public:
        DoToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::Do;
    };

    class WhileToken : public Token
    {
    public:
        WhileToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::While;
    };

    class InToken : public Token
    {
    public:
        InToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::In;
    };

    class CamelCaseIdentifierToken : public Token
    {
    public:
        CamelCaseIdentifierToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::CamelCaseIdentifier;
    };

    class PascalCaseIdentifierToken : public Token
    {
    public:
        PascalCaseIdentifierToken(std::string string)
            : Token(string)
            {}
        const TokenType tokenType = TokenType::PascalCaseIdentifier;
    };

}
