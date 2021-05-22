#pragma once
#include <string>
#include "llvm/IR/Module.h"

namespace Decaf {
    class Decaf
    {
        public:
            std::string ConvertToLlvm(llvm::Module& module, std::string decafCode);
            void LoadToLlvmModule(llvm::Module& module, std::string decafCode);
        private:

    };
}
