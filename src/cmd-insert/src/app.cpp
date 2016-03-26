#include <llvm/Support/CommandLine.h>
#include <string>
#include <iostream>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include "actions.hpp"

static llvm::cl::OptionCategory AutopledgeInsertCategory("autopledge-insert options");

int main(int argc, const char **argv) {
    /*llvm::cl::ParseCommandLineOptions(argc, argv);*/

    clang::tooling::CommonOptionsParser optionsParser(argc, argv, AutopledgeInsertCategory);
    std::vector<std::string> v;
    clang::tooling::ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    auto action = clang::tooling::newFrontendActionFactory<autopledge::ExampleFrontendAction>();
    int result = tool.run(action.get());

    /*auto& sourceManager = autopledge::rewriter.getSourceMgr();
    auto mainFileId = sourceManager.getMainFileID();*/
    /*auto& rw = autopledge::rewriter;
    auto& editBuffer = rw.buffer_begin()->second;
    editBuffer.write(llvm::errs());*/

    return result;
}