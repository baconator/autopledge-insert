#include "llvm/Support/CommandLine.h"
#include <string>
#include <sstream>
#include <iostream>
#include "llvm/AsmParser/Parser.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include "pass.hpp"


using namespace std;
using namespace llvm;
using llvm::legacy::PassManager;

namespace autopledge {

    static llvm::cl::opt<bool> Quiet("quiet",
                                     llvm::cl::desc("Disable all output not relating to compilation."));
    static llvm::cl::list<std::string> Targets(llvm::cl::Positional,
                                               llvm::cl::desc("[<file>,...]"),
                                               llvm::cl::OneOrMore);

}

namespace {
    cl::opt<string>
            inPath{cl::Positional,
                   cl::desc("<Module to analyze>"),
                   cl::value_desc("bitcode filename"), cl::Required};
}

int main(int argc, const char **argv) {
    sys::PrintStackTraceOnErrorSignal();
    llvm::PrettyStackTraceProgram X{argc, argv};
    llvm_shutdown_obj shutdown;
    cl::ParseCommandLineOptions(argc, argv);

    // Construct an IR file from the filename passed on the command line.
    LLVMContext &context = getGlobalContext();
    SMDiagnostic err;
    unique_ptr<Module> module = llvm::parseIRFile(inPath.getValue(), err, context);

    if (!module.get()) {
        errs() << "Error reading bitcode file.\n";
        err.print(argv[0], errs());
        return -1;
    }

    PassManager pm;
    pm.add(new autopledge::AnnotateSyscalls());
    pm.run(*module);
}