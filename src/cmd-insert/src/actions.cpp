#pragma once

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    // TODO: handle arbitrary input for handoff to compiler.
    /*static llvm::cl::opt<std::string> Files( "input",
                                             llvm::cl::desc("[<file>,...]"));*/

    /*static llvm::cl::OptionCategory AutopledgeInsertCategory("autopledge-insert options");*/


    clang::Rewriter rewriter;
    int numFunctions = 0;

    struct ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor> {
        clang::ASTContext& astContext;

        ExampleVisitor(clang::CompilerInstance *CI)
                : astContext(CI->getASTContext()) // initialize private members
        {
            llvm::outs() << "SET THE REWRITER SOURCE MANAGER\n";
            auto& sourceManager = astContext.getSourceManager();
            auto& langOpts = astContext.getLangOpts();
            rewriter = clang::Rewriter(sourceManager, langOpts);
        }

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func) {
            llvm::outs() << "HIT VISIT DECL\n";
            numFunctions++;
            auto funcName = func->getNameInfo().getName().getAsString();
            if (funcName == "do_math") {
                rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
                llvm::errs() << "** Rewrote function def: " << funcName << "\n";
            }
            return true;
        }

        virtual bool VisitStmt(clang::Stmt *st) {
            llvm::outs() << "HIT VISIT STMT\n";
            if (auto *ret = llvm::dyn_cast<clang::ReturnStmt>(st)) {
                rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
                llvm::errs() << "** Rewrote ReturnStmt\n";
            }
            if (auto *call = llvm::dyn_cast<clang::CallExpr>(st)) {
                rewriter.ReplaceText(call->getLocStart(), 7, "add5");
                llvm::errs() << "** Rewrote function call\n";
            }
            return true;
        }

    };

    struct ExampleASTConsumer : public clang::ASTConsumer {
        ExampleVisitor *visitor;

        ExampleASTConsumer(clang::CompilerInstance *CI) : visitor(new ExampleVisitor(CI)) { }

        virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG) {
            // a DeclGroupRef may have multiple Decls, so we iterate through each one
            llvm::outs() << "HIT HANDLE DECL WHATEVER\n";
            for (auto D : DG) {
                visitor->TraverseDecl(D); // recursively visit each AST node in Decl "D"
            }
            return true;
        }
    };

    struct ExampleFrontendAction : public clang::ASTFrontendAction {
        virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file) override {
            llvm::outs() << "HIT AN EXAMPLE FRONTEND ACTION\n";
            return std::make_unique<ExampleASTConsumer>(&CI); // pass CI pointer to ASTConsumer
        }
    };
}