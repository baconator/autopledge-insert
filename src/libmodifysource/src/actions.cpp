#include "actions.hpp"

namespace autopledge {
    ExampleVisitor::ExampleVisitor(clang::CompilerInstance *CI, ExampleActionOutput &result)
            : astContext(CI->getASTContext()), result(result) // initialize private members
    {
        llvm::outs() << "SET THE REWRITER SOURCE MANAGER\n";
        auto& sourceManager = astContext.getSourceManager();
        auto& langOpts = astContext.getLangOpts();
        result.rewriter = clang::Rewriter(sourceManager, langOpts);
    }

    bool ExampleVisitor::VisitFunctionDecl(clang::FunctionDecl *func) {
        llvm::outs() << "HIT VISIT DECL\n";
        result.numFunctions++;
        auto funcName = func->getNameInfo().getName().getAsString();
        if (funcName == "do_math") {
            result.rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
            llvm::errs() << "** Rewrote function def: " << funcName << "\n";
        }
        return true;
    }

    bool ExampleVisitor::VisitStmt(clang::Stmt *st) {
        llvm::outs() << "HIT VISIT STMT\n";
        if (auto *ret = llvm::dyn_cast<clang::ReturnStmt>(st)) {
            result.rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
            llvm::errs() << "** Rewrote ReturnStmt\n";
        }
        if (auto *call = llvm::dyn_cast<clang::CallExpr>(st)) {
            result.rewriter.ReplaceText(call->getLocStart(), 7, "add5");
            llvm::errs() << "** Rewrote function call\n";
        }
        return true;
    }

    ExampleASTConsumer::ExampleASTConsumer(clang::CompilerInstance *CI, ExampleActionOutput &result) : visitor(new ExampleVisitor(CI, result)), result(result) { }

    bool ExampleASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef DG) {
        // a DeclGroupRef may have multiple Decls, so we iterate through each one
        llvm::outs() << "HIT HANDLE DECL WHATEVER\n";
        for (auto D : DG) {
            visitor->TraverseDecl(D); // recursively visit each AST node in Decl "D"
        }
        return true;
    }

    std::unique_ptr<clang::ASTConsumer> ExampleFrontendAction::CreateASTConsumer(clang::CompilerInstance& CI,
                                                                                           StringRef file) {
        llvm::outs() << "HIT AN EXAMPLE FRONTEND ACTION\n";
        return std::make_unique<autopledge::ExampleASTConsumer>(&CI, result); // pass CI pointer to ASTConsumer
    }
}