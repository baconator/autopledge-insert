namespace autopledge {

    enum SyscallType {
        // TODO: use real types in pledge(2)
        stTemp1,
        stTemp2,
        NOT_SYSCALL
    };

    struct Syscall {
        SyscallType type;
        Syscall(SyscallType type);
        static SyscallType getSyscallType(llvm::StringRef);
    };

    inline bool operator<(const Syscall& lhs, const Syscall& rhs)
    {
        return lhs.type < rhs.type;
    }
}