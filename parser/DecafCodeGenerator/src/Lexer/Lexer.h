#include <string>
#include "Token/Tokens.h"

namespace Decaf
{
    class Lexer
    {

    public:
        Lexer(std::string code);
        Token GetNextToken();

    private:
        char GetNextChar();

    private:
        std::string _code;
    };
}
