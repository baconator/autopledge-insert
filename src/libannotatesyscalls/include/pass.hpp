#pragma once

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <set>
#include "syscall.hpp"

namespace autopledge {
    struct AnnotateSyscalls : public llvm::ModulePass {
        static char ID;
        AnnotateSyscalls() : ModulePass(ID) { }

        bool runOnModule(llvm::Module& m) override;

        // TODO: make this less hideously unsafe (i.e. shouldn't rely on pointer identity after a cycle)
        std::map<llvm::BasicBlock*, std::set<autopledge::Syscall>> basicBlockToSyscallConstraints;
        std::map<llvm::Function*, std::set<autopledge::Syscall>> functionToSyscallConstraints;
    };
}