#include "actions.hpp"

namespace autopledge {
    InsertPledgesVisitor::InsertPledgesVisitor(clang::CompilerInstance *CI, InsertPledgesState &result)
            : astContext(CI->getASTContext()), state(result) // initialize private members
    {
        llvm::outs() << "SET THE REWRITER SOURCE MANAGER\n";
        auto &sourceManager = astContext.getSourceManager();
        auto &langOpts = astContext.getLangOpts();
        result.rewriter = clang::Rewriter(sourceManager, langOpts);
    }

    bool InsertPledgesVisitor::VisitFunctionDecl(clang::FunctionDecl *func) {
        llvm::outs() << "HIT VISIT DECL\n";
        auto funcBody = func->getBody();
        auto sourceCfg = clang::CFG::buildCFG(func, funcBody, &astContext, clang::CFG::BuildOptions());
        auto &root = sourceCfg->getEntry();
        for (auto successor = root.succ_begin(); successor < root.succ_end(); successor = std::next(successor)) {
            
        }

        state.numFunctions++;
        auto funcName = func->getNameInfo().getName().getAsString();
        if (funcName == "do_math") {
            state.rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
            llvm::errs() << "** Rewrote function def: " << funcName << "\n";
        }
        return true;
    }

    bool InsertPledgesVisitor::VisitStmt(clang::Stmt *st) {
        llvm::outs() << "HIT VISIT STMT\n";
        if (auto *ret = llvm::dyn_cast<clang::ReturnStmt>(st)) {
            state.rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
            llvm::errs() << "** Rewrote ReturnStmt\n";
        }
        if (auto *call = llvm::dyn_cast<clang::CallExpr>(st)) {
            state.rewriter.ReplaceText(call->getLocStart(), 7, "add5");
            llvm::errs() << "** Rewrote function call\n";
        }
        return true;
    }

    InsertPledgesConsumer::InsertPledgesConsumer(clang::CompilerInstance *CI, InsertPledgesState &result) : visitor(
            new InsertPledgesVisitor(CI, result)), state(result) { }

    bool InsertPledgesConsumer::HandleTopLevelDecl(clang::DeclGroupRef DG) {
        // a DeclGroupRef may have multiple Decls, so we iterate through each one
        llvm::outs() << "HIT HANDLE DECL WHATEVER\n";
        for (auto D : DG) {
            visitor->TraverseDecl(D); // recursively visit each AST node in Decl "D"
        }
        return true;
    }

    std::unique_ptr<clang::ASTConsumer> InsertPledges::CreateASTConsumer(clang::CompilerInstance &CI,
                                                                         StringRef file) {
        llvm::outs() << "HIT AN EXAMPLE FRONTEND ACTION\n";
        return std::make_unique<autopledge::InsertPledgesConsumer>(&CI, state); // pass CI pointer to ASTConsumer
    }

    InsertPledges::InsertPledges(InsertPledgesState &result) : state(result) { }
}