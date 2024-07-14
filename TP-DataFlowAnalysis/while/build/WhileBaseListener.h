
#include <iostream>
#include <list>

#include "WhileLang.h"
#include "WhileCFG.h"


// Generated from /cal/exterieurs/benmbarek-23/Desktop/TP/S2/SE206/youssef-ben-mbarek/TP1/while/src/While.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "WhileListener.h"


/**
 * This class provides an empty implementation of WhileListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  WhileBaseListener : public WhileListener {
public:

  virtual void enterProgram(WhileParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(WhileParser::ProgramContext * /*ctx*/) override { }

  virtual void enterParam_decl(WhileParser::Param_declContext * /*ctx*/) override { }
  virtual void exitParam_decl(WhileParser::Param_declContext * /*ctx*/) override { }

  virtual void enterInt_init(WhileParser::Int_initContext * /*ctx*/) override { }
  virtual void exitInt_init(WhileParser::Int_initContext * /*ctx*/) override { }

  virtual void enterArray_init(WhileParser::Array_initContext * /*ctx*/) override { }
  virtual void exitArray_init(WhileParser::Array_initContext * /*ctx*/) override { }

  virtual void enterVar_def(WhileParser::Var_defContext * /*ctx*/) override { }
  virtual void exitVar_def(WhileParser::Var_defContext * /*ctx*/) override { }

  virtual void enterCall_args(WhileParser::Call_argsContext * /*ctx*/) override { }
  virtual void exitCall_args(WhileParser::Call_argsContext * /*ctx*/) override { }

  virtual void enterExUnequal(WhileParser::ExUnequalContext * /*ctx*/) override { }
  virtual void exitExUnequal(WhileParser::ExUnequalContext * /*ctx*/) override { }

  virtual void enterExCall(WhileParser::ExCallContext * /*ctx*/) override { }
  virtual void exitExCall(WhileParser::ExCallContext * /*ctx*/) override { }

  virtual void enterExLessEqual(WhileParser::ExLessEqualContext * /*ctx*/) override { }
  virtual void exitExLessEqual(WhileParser::ExLessEqualContext * /*ctx*/) override { }

  virtual void enterExID(WhileParser::ExIDContext * /*ctx*/) override { }
  virtual void exitExID(WhileParser::ExIDContext * /*ctx*/) override { }

  virtual void enterExLess(WhileParser::ExLessContext * /*ctx*/) override { }
  virtual void exitExLess(WhileParser::ExLessContext * /*ctx*/) override { }

  virtual void enterExExpr(WhileParser::ExExprContext * /*ctx*/) override { }
  virtual void exitExExpr(WhileParser::ExExprContext * /*ctx*/) override { }

  virtual void enterExPlus(WhileParser::ExPlusContext * /*ctx*/) override { }
  virtual void exitExPlus(WhileParser::ExPlusContext * /*ctx*/) override { }

  virtual void enterExEqual(WhileParser::ExEqualContext * /*ctx*/) override { }
  virtual void exitExEqual(WhileParser::ExEqualContext * /*ctx*/) override { }

  virtual void enterExN(WhileParser::ExNContext * /*ctx*/) override { }
  virtual void exitExN(WhileParser::ExNContext * /*ctx*/) override { }

  virtual void enterExArray(WhileParser::ExArrayContext * /*ctx*/) override { }
  virtual void exitExArray(WhileParser::ExArrayContext * /*ctx*/) override { }

  virtual void enterExArrayAddr(WhileParser::ExArrayAddrContext * /*ctx*/) override { }
  virtual void exitExArrayAddr(WhileParser::ExArrayAddrContext * /*ctx*/) override { }

  virtual void enterExAddr(WhileParser::ExAddrContext * /*ctx*/) override { }
  virtual void exitExAddr(WhileParser::ExAddrContext * /*ctx*/) override { }

  virtual void enterExMinus(WhileParser::ExMinusContext * /*ctx*/) override { }
  virtual void exitExMinus(WhileParser::ExMinusContext * /*ctx*/) override { }

  virtual void enterExMult(WhileParser::ExMultContext * /*ctx*/) override { }
  virtual void exitExMult(WhileParser::ExMultContext * /*ctx*/) override { }

  virtual void enterExDiv(WhileParser::ExDivContext * /*ctx*/) override { }
  virtual void exitExDiv(WhileParser::ExDivContext * /*ctx*/) override { }

  virtual void enterExPtr(WhileParser::ExPtrContext * /*ctx*/) override { }
  virtual void exitExPtr(WhileParser::ExPtrContext * /*ctx*/) override { }

  virtual void enterStmtsThen(WhileParser::StmtsThenContext * /*ctx*/) override { }
  virtual void exitStmtsThen(WhileParser::StmtsThenContext * /*ctx*/) override { }

  virtual void enterStmtsElse(WhileParser::StmtsElseContext * /*ctx*/) override { }
  virtual void exitStmtsElse(WhileParser::StmtsElseContext * /*ctx*/) override { }

  virtual void enterStmtsWhile(WhileParser::StmtsWhileContext * /*ctx*/) override { }
  virtual void exitStmtsWhile(WhileParser::StmtsWhileContext * /*ctx*/) override { }

  virtual void enterStmtVar(WhileParser::StmtVarContext * /*ctx*/) override { }
  virtual void exitStmtVar(WhileParser::StmtVarContext * /*ctx*/) override { }

  virtual void enterStmtAssign(WhileParser::StmtAssignContext * /*ctx*/) override { }
  virtual void exitStmtAssign(WhileParser::StmtAssignContext * /*ctx*/) override { }

  virtual void enterStmtArrayAssign(WhileParser::StmtArrayAssignContext * /*ctx*/) override { }
  virtual void exitStmtArrayAssign(WhileParser::StmtArrayAssignContext * /*ctx*/) override { }

  virtual void enterStmtPtrAssign(WhileParser::StmtPtrAssignContext * /*ctx*/) override { }
  virtual void exitStmtPtrAssign(WhileParser::StmtPtrAssignContext * /*ctx*/) override { }

  virtual void enterStmtExpr(WhileParser::StmtExprContext * /*ctx*/) override { }
  virtual void exitStmtExpr(WhileParser::StmtExprContext * /*ctx*/) override { }

  virtual void enterStmtIf(WhileParser::StmtIfContext * /*ctx*/) override { }
  virtual void exitStmtIf(WhileParser::StmtIfContext * /*ctx*/) override { }

  virtual void enterStmtWhile(WhileParser::StmtWhileContext * /*ctx*/) override { }
  virtual void exitStmtWhile(WhileParser::StmtWhileContext * /*ctx*/) override { }

  virtual void enterStmtReturn(WhileParser::StmtReturnContext * /*ctx*/) override { }
  virtual void exitStmtReturn(WhileParser::StmtReturnContext * /*ctx*/) override { }

  virtual void enterFun_body(WhileParser::Fun_bodyContext * /*ctx*/) override { }
  virtual void exitFun_body(WhileParser::Fun_bodyContext * /*ctx*/) override { }

  virtual void enterParameters(WhileParser::ParametersContext * /*ctx*/) override { }
  virtual void exitParameters(WhileParser::ParametersContext * /*ctx*/) override { }

  virtual void enterFun_def(WhileParser::Fun_defContext * /*ctx*/) override { }
  virtual void exitFun_def(WhileParser::Fun_defContext * /*ctx*/) override { }

  virtual void enterVar(WhileParser::VarContext * /*ctx*/) override { }
  virtual void exitVar(WhileParser::VarContext * /*ctx*/) override { }

  virtual void enterFun(WhileParser::FunContext * /*ctx*/) override { }
  virtual void exitFun(WhileParser::FunContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

