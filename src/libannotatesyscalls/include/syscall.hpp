namespace autopledge {

    enum SyscallType {
        // TODO: use real types in pledge(2)
        UNDEFINED,
        UNKNOWN,
        stTemp1,
        stTemp2
    };

    struct Syscall {
        SyscallType type;
        Syscall();
        Syscall(SyscallType type);
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