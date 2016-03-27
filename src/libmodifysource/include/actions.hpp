#pragma once

#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    /*clang::Rewriter rewriter;
    int numFunctions = 0;*/

    struct ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor> {
        clang::ASTContext& astContext;

        ExampleVisitor(clang::CompilerInstance *CI);

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func);

        virtual bool VisitStmt(clang::Stmt *st);

    };

    struct ExampleASTConsumer : public clang::ASTConsumer {
        ExampleVisitor *visitor;

        ExampleASTConsumer(clang::CompilerInstance *CI);

        virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG);
    };

    struct ExampleFrontendAction : public clang::ASTFrontendAction {
        virtual std::unique_ptr <clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file);
    };
}