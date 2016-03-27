namespace autopledge {

    enum SyscallType {
        // TODO: use real types in pledge(2)
        NOT_SYSCALL,
        stTemp1,
        stTemp2,
        UNDEFINED,
        UNKNOWN
    };

    struct Syscall {
        SyscallType type;
        Syscall(SyscallType type);
        Syscall(llvm::StringRef fName);
        static SyscallType getSyscallType(llvm::StringRef);
    };

    inline bool operator<(const Syscall& lhs, const Syscall& rhs)
    {
        return lhs.type < rhs.type;
    }

    inline bool operator==(const Syscall& lhs, const Syscall& rhs)
    {
        return lhs.type == rhs.type;
    }
}