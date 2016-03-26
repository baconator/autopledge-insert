#include "llvm/Support/CommandLine.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

namespace autopledge {

    static llvm::cl::opt<bool> Quiet("quiet",
                                     llvm::cl::desc("Disable all output not relating to compilation."));
    static llvm::cl::list<std::string> Targets(llvm::cl::Positional,
                                               llvm::cl::desc("[<file>,...]"),
                                               llvm::cl::OneOrMore);

}

int main(int argc, const char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);

    std::cout << "test!\n";
}