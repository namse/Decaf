#include "Decaf.h"
#include <fstream>
#include <string>
#include <iostream>
#include "CLI11.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

int main(int argc, char **argv)
{

  CLI::App app{"Decaf Cli"};

  std::string inputFilePath = "";
  std::string outputDirectoryPath = "";
  app.add_option("-i,--input", inputFilePath, "input .dc file path")
    ->required()
    ->check(CLI::ExistingFile);
  app.add_option("-o,--output", outputDirectoryPath, "output directory path for output.ll file")
    ->required()
    ->check(CLI::ExistingDirectory);

  CLI11_PARSE(app, argc, argv);

  std::ifstream inputFileStream(inputFilePath);
  auto outputFilePath = fs::path(outputDirectoryPath).append("output.ll").string();
  std::ofstream outputFileStream(outputFilePath);

  std::stringstream buffer;
  buffer << inputFileStream.rdbuf();

  auto decafFileString = buffer.str();

  Decaf::Decaf decaf;
  auto result = decaf.ConvertToLLVM(decafFileString);

  std::cout << result << std::endl;
  outputFileStream << result << std::endl;

  return 0;
}
