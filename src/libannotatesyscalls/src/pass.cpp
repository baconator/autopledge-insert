#include "pass.hpp"
#include "llvm/IR/CallSite.h"


using namespace llvm;
using namespace std;

static const Function *getCalledFunction(const CallSite cs) {
    if (!cs.getInstruction()) {
        return nullptr;
    }

    const Value *called = cs.getCalledValue()->stripPointerCasts();
    return dyn_cast<Function>(called);
}

namespace autopledge {
    char autopledge::AnnotateSyscalls::ID = 0;

    void autopledge::AnnotateSyscalls::insertToBBMapSet(llvm::BasicBlock* key, autopledge::Syscall value) {
        auto bbSet = basicBlockToSyscallConstraints.find(key);
        if (bbSet == basicBlockToSyscallConstraints.end()) {
            std::set<autopledge::Syscall> s;
            s.insert(value);
            basicBlockToSyscallConstraints.insert(std::make_pair(key, s));
        } else {
            bbSet->second.insert(value);
        }
    };

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
                        insertToBBMapSet(&bb, Syscall(syscallType));
                        llvm::outs() << "\t " << fun->getName() << "\n";
                    }
                }
            }
        }
        for(auto it = basicBlockToSyscallConstraints.begin(); it != basicBlockToSyscallConstraints.end(); ++it)
        {
            outs() << it->first << "\t{";
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                outs() << i->type << ", ";
            }
            outs() << "}\n";
        }
        return true;
    }
}