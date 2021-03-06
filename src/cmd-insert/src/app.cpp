#include <llvm/Support/CommandLine.h>
#include <string>
#include <iostream>
#include <fstream>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include "actions.hpp"

int main(int argc, const char **argv) {
    std::ifstream t(argv[1]);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    autopledge::ExampleActionOutput result;
    auto action = new autopledge::ExampleFrontendAction(result);
    clang::tooling::runToolOnCode(action, str, argv[1]);

    auto& rw = result.rewriter;
    auto& editBuffer = rw.buffer_begin()->second;
    editBuffer.write(llvm::errs());

    return 1;
}