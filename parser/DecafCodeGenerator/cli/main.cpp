#include "Decaf.h"
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include "CLI11.hpp"
#include <experimental/filesystem>
#include "llvm/ADT/Optional.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
namespace fs = std::experimental::filesystem;

int ParseArgs(int argc, char **argv, std::string &inputFilePath, std::string &outputDirectoryPath, std::string &type)
{
    CLI::App app{"Decaf Cli"};
    app.add_option("-i,--input", inputFilePath, "input .dc file path")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("-o,--output", outputDirectoryPath, "output directory path for output.o file")
        ->required()
        ->check(CLI::ExistingDirectory);
    app.add_option("-t,--type", type, "output file type. ll or o. default is o")
        ->required()
        ->check([](auto input) {
            if (input != "o" && input != "ll")
            {
                return "type should be o or ll";
            }
            return "";
        });

    CLI11_PARSE(app, argc, argv);
    return 0;
}

std::string ReadInputFile(const std::string &inputFilePath)
{
    std::ifstream inputFileStream(inputFilePath);

    std::stringstream buffer;
    buffer << inputFileStream.rdbuf();

    return buffer.str();
}

int OutAsObjectFile(Decaf::Decaf &decaf, llvm::Module &module, std::string &decafFileString, std::string &outputDirectoryPath)
{
    decaf.LoadToLlvmModule(module, decafFileString);

    // Initialize the target registry etc.
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    module.setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target)
    {
        std::cerr << Error;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TheTargetMachine =
        Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    module.setDataLayout(TheTargetMachine->createDataLayout());

    auto filename = "output.o";
    auto outputFilePath = fs::path(outputDirectoryPath).append(filename).string();

    std::error_code EC;
    llvm::raw_fd_ostream dest(outputFilePath, EC, llvm::sys::fs::OF_None);

    if (EC)
    {
        llvm::errs() << "Could not open file: " << EC.message();
        return 1;
    }

    llvm::legacy::PassManager pass;
    auto FileType = llvm::CodeGenFileType::CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
    {
        llvm::errs() << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run(module);
    dest.flush();

    llvm::outs() << "Wrote " << outputFilePath << "\n";

    return 0;
}

int OutAsLlFile(Decaf::Decaf &decaf, llvm::Module &module, std::string &decafFileString, std::string &outputDirectoryPath)
{
    auto llFileString = decaf.ConvertToLlvm(module, decafFileString);
    auto filename = "output.ll";
    auto outputFilePath = fs::path(outputDirectoryPath).append(filename).string();

    std::cout << "Wrote " << outputFilePath << std::endl;
    std::cout << llFileString << std::endl;

    std::ofstream outFileStream(outputFilePath);
    if (!outFileStream.is_open()) {
        std::cerr << "Could not open file: " << std::endl;
        return 1;
    }

    outFileStream << llFileString << std::flush;
    outFileStream.close();

    return 0;
}

int main(int argc, char **argv)
{
    std::string inputFilePath = "";
    std::string outputDirectoryPath = "";
    std::string type = "";
    auto ret = ParseArgs(argc, argv, inputFilePath, outputDirectoryPath, type);
    if (ret)
    {
        return ret;
    }

    auto decafFileString = ReadInputFile(inputFilePath);

    auto context = std::make_unique<llvm::LLVMContext>();
    llvm::Module module("Decaf", *context);
    Decaf::Decaf decaf;

    if (type == "o")
    {
        return OutAsObjectFile(decaf, module, decafFileString, outputDirectoryPath);
    }
    else if (type == "ll")
    {
        return OutAsLlFile(decaf, module, decafFileString, outputDirectoryPath);
    }
}
