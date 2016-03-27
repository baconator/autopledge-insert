#include <llvm/ADT/StringRef.h>
#include "syscall.hpp"

namespace autopledge {
    Syscall::Syscall(SyscallType t) {
        type = t;
    }

    Syscall::Syscall(llvm::StringRef fName) {
        // TODO use actual syscalls listed in pledge(2)
        if (fName.equals("stub1") || fName.equals("stub3")) {
            type = SyscallType::stTemp1;
        } else if (fName.equals("stub2")) {
            type = SyscallType::stTemp2;
        } else {
            type = SyscallType::NOT_SYSCALL;
            //shouldn't be here
        }
    }

    SyscallType Syscall::getSyscallType(llvm::StringRef name) {
        // TODO use actual syscalls listed in pledge(2)
        if (name.equals("stub1") || name.equals("stub3")) {
            return SyscallType::stTemp1;
        } else if (name.equals("stub2")) {
            return SyscallType::stTemp2;
        } else {
            return SyscallType::NOT_SYSCALL;
        }
    }
}