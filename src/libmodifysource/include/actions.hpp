#pragma once

#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    struct InsertPledgesState {
        InsertPledgesState(const InsertPledgesState& o) = delete;
        InsertPledgesState(){}
        clang::Rewriter rewriter;
        int numFunctions = 0;
    };

    struct InsertPledgesVisitor : public clang::RecursiveASTVisitor<InsertPledgesVisitor> {
        InsertPledgesVisitor(clang::CompilerInstance *CI, InsertPledgesState &result);

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func);

        virtual bool VisitStmt(clang::Stmt *st);

    private:
        clang::ASTContext& astContext;
        InsertPledgesState &state;
    };

    struct InsertPledgesConsumer : public clang::ASTConsumer {
        InsertPledgesConsumer(clang::CompilerInstance *CI, InsertPledgesState &result);

        virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG);

    private:
        InsertPledgesVisitor *visitor;
        InsertPledgesState &state;
    };

    struct InsertPledges : public clang::ASTFrontendAction {
        InsertPledges(InsertPledgesState &result);
        virtual std::unique_ptr <clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file);

    private:
        InsertPledgesState &state;
    };


}