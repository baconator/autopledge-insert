#include <llvm/Support/CommandLine.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

namespace autopledge {
    // TODO: handle arbitrary input for handoff to compiler.
    static llvm::cl::list<std::string> Files(llvm::cl::Positional,
                                               llvm::cl::desc("[<file>,...]"),
                                               llvm::cl::OneOrMore);

    static llvm::cl::OptionCategory AutopledgeInsertCategory("autopledge-insert options");
}

int main(int argc, const char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);

    clang::tooling::CommonOptionsParser optionsParser(argc, argv, autopledge::AutopledgeInsertCategory);
    clang::tooling::ClangTool tool(optionsParser.getCompilations(), autopledge::Files);

}