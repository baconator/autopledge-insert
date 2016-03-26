#include "pass.hpp"

namespace autopledge {
    char autopledge::AnnotateSyscalls::ID = 0;

    bool autopledge::AnnotateSyscalls::runOnModule(llvm::Module &m) {
        for (auto &f : m) {
            llvm::outs() << f.getName() << "\n";
            for (auto &bb : f) {
                for (auto &i : bb) {
                }
            }
        }
        return false;
    }
}