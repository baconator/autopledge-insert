#include <llvm/Support/CommandLine.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace autopledge {
    // TODO: handle arbitrary input for handoff to compiler.
    static llvm::cl::list<std::string> Files(llvm::cl::Positional,
                                             llvm::cl::desc("[<file>,...]"),
                                             llvm::cl::OneOrMore);

    static llvm::cl::OptionCategory AutopledgeInsertCategory("autopledge-insert options");


    clang::Rewriter rewriter;
    int numFunctions = 0;

    struct ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor> {
        clang::ASTContext& astContext;

        ExampleVisitor(clang::CompilerInstance *CI)
                : astContext(CI->getASTContext()) // initialize private members
        {
            rewriter.setSourceMgr(astContext.getSourceManager(),
                                  astContext.getLangOpts());
        }

        virtual bool VisitFunctionDecl(clang::FunctionDecl *func) {
            numFunctions++;
            auto funcName = func->getNameInfo().getName().getAsString();
            if (funcName == "do_math") {
                rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
                llvm::errs() << "** Rewrote function def: " << funcName << "\n";
            }
            return true;
        }

        virtual bool VisitStmt(clang::Stmt *st) {
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
            for (auto D : DG) {
                //visitor->TraverseDecl(D); // recursively visit each AST node in Decl "D"
            }
            return true;
        }
    };

    struct ExampleFrontendAction : public clang::ASTFrontendAction {
        virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, StringRef file) {
            return std::make_unique<ExampleASTConsumer>(&CI); // pass CI pointer to ASTConsumer
        }
    };
}

int main(int argc, const char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);

    clang::tooling::CommonOptionsParser optionsParser(argc, argv, autopledge::AutopledgeInsertCategory);
    clang::tooling::ClangTool tool(optionsParser.getCompilations(), autopledge::Files);


}