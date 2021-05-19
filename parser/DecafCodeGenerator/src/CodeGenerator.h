#pragma once
#include <string>

namespace Decaf {
    class CodeGenerator
    {
        public:
            std::string ConvertToLLVM(std::string decafCode);
        private:

    };
}
