#include <llvm/Support/CommandLine.h>
#include <string>
#include <sstream>
#include <iostream>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include "actions.cpp"

int main(int argc, const char **argv) {
    /*llvm::cl::ParseCommandLineOptions(argc, argv);*/

    clang::tooling::CommonOptionsParser optionsParser(argc, argv, autopledge::AutopledgeInsertCategory);
    std::vector<std::string> v;
    clang::tooling::ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    auto action = clang::tooling::newFrontendActionFactory<autopledge::ExampleFrontendAction>();
    int result = tool.run(action.get());

    auto& sourceManager = autopledge::rewriter.getSourceMgr();
    auto mainFileId = sourceManager.getMainFileID();
    auto& rewriter = autopledge::rewriter;
    auto& editBuffer = rewriter.buffer_begin()->second;
    editBuffer.write(llvm::errs());

    return result;
}