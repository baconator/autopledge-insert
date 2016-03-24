#pragma once

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <set>
#include "syscall.hpp"

namespace autopledge {
    struct AnnotateSyscalls : public llvm::ModulePass {
        static char ID;
        AnnotateSyscalls() : ModulePass(ID) { }

        bool runOnModule(llvm::Module& m) override { }

        std::map<std::string, std::set<autopledge::Syscall>> symbolNameToSyscallConstraints;
    };
}