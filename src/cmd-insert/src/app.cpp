#include <llvm/Support/CommandLine.h>
#include <string>
#include <iostream>
#include <fstream>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include "actions.hpp"

int main(int argc, const char **argv) {
    std::ifstream sourceFile(argv[1]);
    std::string str((std::istreambuf_iterator<char>(sourceFile)),
                    std::istreambuf_iterator<char>());

    autopledge::InsertPledgesState result;
    auto action = new autopledge::InsertPledges(result);
    clang::tooling::runToolOnCode(action, str, argv[1]);

    auto& rw = result.rewriter;
    auto& editBuffer = rw.buffer_begin()->second;
    editBuffer.write(llvm::errs());

    return 1;
}