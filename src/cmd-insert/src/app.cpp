#include "llvm/Support/CommandLine.h"
#include <string>

static llvm::cl::opt<bool> BeAwesome("awesome-mode", llvm::cl::desc("Enable super awesome extra feature."),
                                     llvm::cl::Required);

int main(int argc, char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);
}