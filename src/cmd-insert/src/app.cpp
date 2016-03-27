#include <llvm/Support/CommandLine.h>
#include <string>
#include <iostream>
#include <fstream>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include "actions.hpp"

/*static llvm::cl::OptionCategory AutopledgeInsertCategory("autopledge-insert options");*/

int main(int argc, const char **argv) {
    /*llvm::cl::ParseCommandLineOptions(argc, argv);*/

    /*clang::tooling::CommonOptionsParser optionsParser(argc, argv, AutopledgeInsertCategory);
    std::vector<std::string> v;*/
    /*clang::tooling::ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());*/

    std::ifstream t(argv[1]);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    auto action = new autopledge::ExampleFrontendAction();
    clang::tooling::runToolOnCode(action, str, argv[1]);

    auto& rw = action->result.rewriter;
    auto& editBuffer = rw.buffer_begin()->second;
    editBuffer.write(llvm::errs());

    return 1;
}