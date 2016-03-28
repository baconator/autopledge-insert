#include "pass.hpp"
#include "llvm/IR/CallSite.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"

#include <unordered_map>
#include <unordered_set>
#include <deque>


using namespace llvm;
using namespace std;

using StateMap = std::unordered_map<llvm::Instruction*, std::set<autopledge::Syscall>>;

static const Function *getCalledFunction(const CallSite cs) {
    if (!cs.getInstruction()) {
        return nullptr;
    }

    const Value *called = cs.getCalledValue()->stripPointerCasts();
    return dyn_cast<Function>(called);
}

class WorkList {
    unordered_set<BasicBlock*> inList;
    deque<BasicBlock*> work;

public:

    template<typename IterTy>
    WorkList(IterTy i, IterTy e)
            : inList{i, e},
              work{i, e} {
    }

    bool empty() { return work.empty(); }

    void add(BasicBlock *bb) {
        if (!inList.count(bb)) {
            work.push_back(bb);
        }
    }

    BasicBlock * take() {
        auto *front = work.front();
        work.pop_front();
        inList.erase(front);
        return front;
    }
};


namespace autopledge {
    char autopledge::AnnotateSyscalls::ID = 0;

    void autopledge::AnnotateSyscalls::insertToMapSets(llvm::Instruction* key, autopledge::Syscall value) {
        auto bb = key->getParent();
        auto function = bb->getParent();
        auto bbSetItem = basicBlockToSyscallConstraints.find(bb);
        auto functionSetItem = functionToSyscallConstraints.find(function);
        std::set<autopledge::Syscall> s; s.insert(value);

        if (bbSetItem == basicBlockToSyscallConstraints.end()) {
            basicBlockToSyscallConstraints.insert(std::make_pair(bb, s));
        } else {
            bbSetItem->second.insert(value);
        }
        if (functionSetItem == functionToSyscallConstraints.end()) {
            functionToSyscallConstraints.insert(std::make_pair(function, s));
        } else {
            functionSetItem->second.insert(value);
        }
    };


    void meet(StateMap &dest, const StateMap &src) {
        for (auto &kvPair : src) {
            const auto found = dest.find(kvPair.first);
            if (found == dest.end()) {
                dest.insert(kvPair);
            } else {
                found->second.insert(kvPair.second.begin(), kvPair.second.end());
            }
        }
    }

    void transfer(Instruction &i, StateMap &state) {
//        if (auto *li = dyn_cast<LoadInst>(&i)) {
//            state[li] = std::set<autopledge::Syscall>();
//            return;
//        }

        const CallSite cs{&i};
        const auto *fun = getCalledFunction(cs);
        // Pretend that indirect calls & non calls don't exist for this analysis
        if (!fun) {
            return;
        }

        // Apply the transfer function to the abstract state
        auto syscallType = Syscall::getSyscallType(fun->getName());
        if (syscallType != SyscallType::UNKNOWN) {
            state[&i].insert(Syscall(syscallType));
        } else {
            // need the callgraph here...
        }

    }

    std::unordered_map<Instruction*,std::pair<StateMap,StateMap>> computeSyscallState(Function &f) {
        // Initialize the abstract state of all BasicBlocks
        std::unordered_map<Instruction*,std::pair<StateMap,StateMap>> abstractState;
        for (auto &bb : f) {
            abstractState[bb.getTerminator()] = std::make_pair(StateMap{},StateMap{});
        }

        // First add all blocks to the worklist in topological order for efficiency
        ReversePostOrderTraversal<Function*> rpot{&f};
        WorkList work{begin(rpot), end(rpot)};

        while (!work.empty()) {
            auto *bb = work.take();

            // Save a copy of the initial and final abstract state to check for changes.
            auto oldExitState   = abstractState[bb->getTerminator()];
            auto &oldEntryState = abstractState[&*bb->begin()];

            // Merge the state coming in from all predecessors
            auto state = StateMap();
            for (pred_iterator PI = pred_begin(bb), E = pred_end(bb); PI != E; ++PI) {
                BasicBlock *Pred = *PI;
                meet(state, abstractState[Pred->getTerminator()].second);
            }

            // If we have already processed the block and no changes have been made to
            // the abstract input, we can skip processing the block.
            if (state == oldEntryState.first && !state.empty()) {
                continue;
            }

            // Propagate through all instructions in the block
            for (auto &i : *bb) {
                abstractState[&i].first = state;
                transfer(i, state);
                abstractState[&i].second = state;
            }

            // If the abstract state for this block did not change, then we are done
            // with this block. Otherwise, we must update the abstract state and
            // consider changes to successors.
            if (state == oldExitState.second) {
                continue;
            }

            for (succ_iterator SU = succ_begin(bb), END = succ_end(bb); SU != END; ++SU) {
                BasicBlock *Succ = *SU;
                work.add(Succ);
            }
        }
//        for(auto it = abstractState.begin(); it != abstractState.end(); ++it)
//        {
//            outs() << "i:" << it->first << ", bb:" << it->first->getParent() << ", f:" << it->first->getParent()->getParent()->getName() << "\t";
//            for (auto i = it->second.first.begin(); i != it->second.first.end(); i++) {
//                outs() << "i:" << i->first << "{";
//                for (auto j = i->second.begin(); j != i->second.end(); j++) {
//                    outs() << j->type << ", ";
//                }
//                outs() << "}";
//
//            }
//            outs() << "\n";
//        }
        return abstractState;
    }

    bool autopledge::AnnotateSyscalls::runOnModule(llvm::Module &m) {
        for (auto &f : m) {
            if (f.getName().equals("main")) {
                auto syscallState = computeSyscallState(f);
                for(auto it = syscallState.begin(); it != syscallState.end(); ++it)
                {
                    for (auto i = it->second.first.begin(); i != it->second.first.end(); i++) {
                        for (auto j = i->second.begin(); j != i->second.end(); j++) {
                            insertToMapSets(i->first, Syscall(j->type));
                        }

                    }
                }
            }
//            for (auto &bb : f) {
//                for (auto &i : bb) {
//                    llvm::CallSite cs(&i);
//                    auto *fun = getCalledFunction(cs);
//                    if (!fun) {
//                        continue;
//                    }
//                    auto syscallType = Syscall::getSyscallType(fun->getName());
//                    if (syscallType != SyscallType::NOT_SYSCALL) {
//                        insertToBBMapSet(&bb, Syscall(syscallType));
//                    }
//                }
//            }
        }
        outs() << "basic blocks system call constraints:\n";
        for(auto it = basicBlockToSyscallConstraints.begin(); it != basicBlockToSyscallConstraints.end(); ++it)
        {
            outs() << "bb:" << it->first << ", function:" << it->first->getParent()->getName() << "\t{";
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                outs() << i->type << " ";
            }
            outs() << "}\n";
        }
        outs() << "\nfunction system call constraints:\n";
        for(auto it = functionToSyscallConstraints.begin(); it != functionToSyscallConstraints.end(); ++it)
        {
            outs() << "function:" << it->first->getName() << "\t{";
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                outs() << i->type << " ";
            }
            outs() << "}\n";
        }
        return true;
    }
}