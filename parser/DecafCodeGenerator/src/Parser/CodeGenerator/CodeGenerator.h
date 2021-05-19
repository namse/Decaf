#pragma once
#include <Parser/Ast/Asts.h>
#include <memory>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

namespace Decaf
{
    class CodeGenerator
    {
    public:
        CodeGenerator();
        void GenerateFunctionCode(std::shared_ptr<FunctionAst> functionAst);
        std::string DumpAllCode();

    private:
        const std::shared_ptr<llvm::LLVMContext> context;
        const std::shared_ptr<llvm::Module> module;
        const std::shared_ptr<llvm::IRBuilder<>> builder;
        const std::map<std::string, llvm::Value *> namedValues;
    };

}
