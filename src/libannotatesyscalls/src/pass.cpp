#include "pass.hpp"
#include "llvm/IR/CallSite.h"


using namespace llvm;

static const Function *getCalledFunction(const CallSite cs) {
    if (!cs.getInstruction()) {
        return nullptr;
    }

    const Value *called = cs.getCalledValue()->stripPointerCasts();
    return dyn_cast<Function>(called);
}

namespace autopledge {
    char autopledge::AnnotateSyscalls::ID = 0;

    bool autopledge::AnnotateSyscalls::runOnModule(llvm::Module &m) {
        for (auto &f : m) {
            llvm::outs() << f.getName() << "\n";
            for (auto &bb : f) {
                for (auto &i : bb) {
                    llvm::CallSite cs(&i);
                    auto *fun = getCalledFunction(cs);
                    if (!fun) {
                        continue;
                    }
                    auto syscallType = Syscall::getSyscallType(fun->getName());
                    if (syscallType != SyscallType::NOT_SYSCALL) {
//                        basicBlockToSyscallConstraints[bb] = Syscall(syscallType);
                        llvm::outs() << "\t " << fun->getName() << "\n";
                    }
                }
            }
        }
        return false;
    }
}