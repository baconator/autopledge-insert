#include "pass.hpp"
#include <iostream>

namespace autopledge {
    char autopledge::AnnotateSyscalls::ID = 0;

    bool autopledge::AnnotateSyscalls::runOnModule(llvm::Module &m) {
        for (auto &f : m) {
            std::cout << f.getName() << std::endl;
            for (auto &bb : f) {
                for (auto &i : bb) {
                }
            }
        }
        return false;
    }
}