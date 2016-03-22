#include <llvm/Support/CommandLine.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <clang/Tooling/Tooling.h>

namespace autopledge {
    // TODO: handle arbitrary input for handoff to compiler.
    static llvm::cl::list<std::string> Files(llvm::cl::Positional,
                                               llvm::cl::desc("[<file>,...]"),
                                               llvm::cl::OneOrMore);

}

int main(int argc, char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);


}