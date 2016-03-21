#pragma once

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "json.hpp"
#include <map>
#include "syscall.hpp"

namespace autopledge {
    struct AnnotateSyscalls : public llvm::ModulePass {
        static char ID;
        AnnotateSyscalls() : ModulePass(ID) { }

        bool runOnModule(llvm::Module& m) override { }

        std::map<std::pair<std::string, unsigned int>, autopledge::Syscall> filenameAndLineToConstraints;
    };
}