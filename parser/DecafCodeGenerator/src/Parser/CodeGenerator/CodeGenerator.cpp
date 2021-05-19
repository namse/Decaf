#include "CodeGenerator.h"

namespace Decaf
{
    CodeGenerator::CodeGenerator()
        : context(std::make_shared<llvm::LLVMContext>()),
          module(std::make_shared<llvm::Module>("Decaf", *context)),
          builder(std::make_shared<llvm::IRBuilder<>>(*context))
    {
    }

    void CodeGenerator::GenerateFunctionCode(std::shared_ptr<FunctionAst> functionAst)
    {
        auto functionName = functionAst->functionNameToken->string;
        auto function = module->getFunction(functionName);
        if (function)
        {
            // already exists. need exception
            return;
        }

        // TODO - paramters type and function type
        std::vector<llvm::Type *> parameterTypes(0);
        auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), parameterTypes, false);

        function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, functionName, module.get());

        // unsigned Idx = 0;
        // for (auto &Arg : F->args())
        //     Arg.setName(Args[Idx++]);

        // return F;

        // Create a new basic block to start insertion into.
        auto basicBlock = llvm::BasicBlock::Create(*context, "entry", function);
        builder->SetInsertPoint(basicBlock);

        // Record the function arguments in the NamedValues map.
        // NamedValues.clear();
        // for (auto &Arg : TheFunction->args())
        //     NamedValues[std::string(Arg.getName())] = &Arg;

        if (functionAst->functionReturnTypeToken->string == "Void") {
            builder->CreateRetVoid();
        }
        // TODO : set return type
        

        // if (Value *RetVal = Body->codegen())
        // {
        //     // Finish off the function.
        //     Builder->CreateRet(RetVal);

        //     // Validate the generated code, checking for consistency.
        //     verifyFunction(*TheFunction);

        //     return TheFunction;
        // }

        // // Error reading body, remove function.
        // TheFunction->eraseFromParent();
        // return nullptr;

        
    }

    std::string CodeGenerator::DumpAllCode()
    {
        std::string code;
        llvm::raw_string_ostream ostream(code);
        ostream << *module;
        ostream.flush();
        return code;
    }

}
