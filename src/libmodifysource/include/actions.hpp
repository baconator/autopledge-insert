#pragma once

#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    struct ExampleActionOutput {
        ExampleActionOutput(const ExampleActionOutput& o) = delete;
        ExampleActionOutput(){}
        clang::Rewriter rewriter;
        int numFunctions = 0;
    };

    struct ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor> {
        ExampleVisitor(clang::CompilerInstance *CI, ExampleActionOutput &result);

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func);

        virtual bool VisitStmt(clang::Stmt *st);

    private:
        clang::ASTContext& astContext;
        ExampleActionOutput &result;
    };

    struct ExampleASTConsumer : public clang::ASTConsumer {
        ExampleASTConsumer(clang::CompilerInstance *CI, ExampleActionOutput &result);

        virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG);

    private:
        ExampleVisitor *visitor;
        ExampleActionOutput &result;
    };

    struct ExampleFrontendAction : public clang::ASTFrontendAction {
        ExampleFrontendAction(ExampleActionOutput &result);
        virtual std::unique_ptr <clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file);

    private:
        ExampleActionOutput &result;
    };


}