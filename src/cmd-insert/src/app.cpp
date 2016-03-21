#include "llvm/Support/CommandLine.h"
#include <string>
#include <sstream>
#include <vector>

static llvm::cl::opt<bool> Quiet("quiet",
                                 llvm::cl::desc("Disable all output not relating to compilation."));
static llvm::cl::opt<std::string> Targets(llvm::cl::Positional,
                                          llvm::cl::desc("[<file>,...]"),
                                          llvm::cl::Required);


int main(int argc, char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);

    // Psh, who manipulates _strings_? Better leave that out of the stdlib.
    // 2d graphics you say? Hmm, good idea.
    std::vector<std::string> targetNames;
    std::stringstream ss(Targets.getValue());
    std::string item;
    while (std::getline(ss, item, ' ')) {
        targetNames.push_back(item);
    }
}