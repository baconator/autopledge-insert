#pragma once

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

namespace autopledge {
    struct AnnotateSyscalls : public llvm::ModulePass {
        static char ID;
    };
}