#pragma once

#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    struct InsertPledgesResult {
        InsertPledgesResult(const InsertPledgesResult& o) = delete;
        InsertPledgesResult(){}
        clang::Rewriter rewriter;
        int numFunctions = 0;
    };

    struct InsertPledgesVisitor : public clang::RecursiveASTVisitor<InsertPledgesVisitor> {
        InsertPledgesVisitor(clang::CompilerInstance *CI, InsertPledgesResult &result);

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func);

        virtual bool VisitStmt(clang::Stmt *st);

    private:
        clang::ASTContext& astContext;
        InsertPledgesResult &result;
    };

    struct InsertPledgesConsumer : public clang::ASTConsumer {
        InsertPledgesConsumer(clang::CompilerInstance *CI, InsertPledgesResult &result);

        virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG);

    private:
        InsertPledgesVisitor *visitor;
        InsertPledgesResult &result;
    };

    struct InsertPledges : public clang::ASTFrontendAction {
        InsertPledges(InsertPledgesResult &result);
        virtual std::unique_ptr <clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file);

    private:
        InsertPledgesResult &result;
    };


}