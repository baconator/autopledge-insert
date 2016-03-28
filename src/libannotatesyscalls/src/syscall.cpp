#include <llvm/ADT/StringRef.h>
#include "syscall.hpp"

namespace autopledge {
    Syscall::Syscall(SyscallType t) {
        type = t;
    }

    Syscall::Syscall() {
        type = SyscallType::UNDEFINED;
    }

    SyscallType Syscall::getSyscallType(llvm::StringRef name) {
        // TODO use actual syscalls listed in pledge(2)
        if (name.equals("stub1") || name.equals("stub3")) {
            return SyscallType::stTemp1;
        } else if (name.equals("stub2")) {
            return SyscallType::stTemp2;
        } else {
            return SyscallType::UNKNOWN;
        }
    }
}