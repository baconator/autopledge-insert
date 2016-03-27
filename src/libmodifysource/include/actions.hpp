#pragma once

#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    struct ExampleActionOutput {
        clang::Rewriter rewriter;
        int numFunctions = 0;
    };

    struct ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor> {
        clang::ASTContext& astContext;
        ExampleActionOutput &result;

        ExampleVisitor(clang::CompilerInstance *CI, ExampleActionOutput &result);

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func);

        virtual bool VisitStmt(clang::Stmt *st);

    };

    struct ExampleASTConsumer : public clang::ASTConsumer {
        ExampleVisitor *visitor;
        ExampleActionOutput &result;

        ExampleASTConsumer(clang::CompilerInstance *CI, ExampleActionOutput &result);

        virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG);
    };

    struct ExampleFrontendAction : public clang::ASTFrontendAction {
        ExampleActionOutput result;
        virtual std::unique_ptr <clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file);
    };


}