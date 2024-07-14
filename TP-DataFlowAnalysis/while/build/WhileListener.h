
#include <iostream>
#include <list>

#include "WhileLang.h"
#include "WhileCFG.h"


// Generated from /cal/exterieurs/benmbarek-23/Desktop/TP/S2/SE206/youssef-ben-mbarek/TP1/while/src/While.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "WhileParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by WhileParser.
 */
class  WhileListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(WhileParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(WhileParser::ProgramContext *ctx) = 0;

  virtual void enterParam_decl(WhileParser::Param_declContext *ctx) = 0;
  virtual void exitParam_decl(WhileParser::Param_declContext *ctx) = 0;

  virtual void enterInt_init(WhileParser::Int_initContext *ctx) = 0;
  virtual void exitInt_init(WhileParser::Int_initContext *ctx) = 0;

  virtual void enterArray_init(WhileParser::Array_initContext *ctx) = 0;
  virtual void exitArray_init(WhileParser::Array_initContext *ctx) = 0;

  virtual void enterVar_def(WhileParser::Var_defContext *ctx) = 0;
  virtual void exitVar_def(WhileParser::Var_defContext *ctx) = 0;

  virtual void enterCall_args(WhileParser::Call_argsContext *ctx) = 0;
  virtual void exitCall_args(WhileParser::Call_argsContext *ctx) = 0;

  virtual void enterExUnequal(WhileParser::ExUnequalContext *ctx) = 0;
  virtual void exitExUnequal(WhileParser::ExUnequalContext *ctx) = 0;

  virtual void enterExCall(WhileParser::ExCallContext *ctx) = 0;
  virtual void exitExCall(WhileParser::ExCallContext *ctx) = 0;

  virtual void enterExLessEqual(WhileParser::ExLessEqualContext *ctx) = 0;
  virtual void exitExLessEqual(WhileParser::ExLessEqualContext *ctx) = 0;

  virtual void enterExID(WhileParser::ExIDContext *ctx) = 0;
  virtual void exitExID(WhileParser::ExIDContext *ctx) = 0;

  virtual void enterExLess(WhileParser::ExLessContext *ctx) = 0;
  virtual void exitExLess(WhileParser::ExLessContext *ctx) = 0;

  virtual void enterExExpr(WhileParser::ExExprContext *ctx) = 0;
  virtual void exitExExpr(WhileParser::ExExprContext *ctx) = 0;

  virtual void enterExPlus(WhileParser::ExPlusContext *ctx) = 0;
  virtual void exitExPlus(WhileParser::ExPlusContext *ctx) = 0;

  virtual void enterExEqual(WhileParser::ExEqualContext *ctx) = 0;
  virtual void exitExEqual(WhileParser::ExEqualContext *ctx) = 0;

  virtual void enterExN(WhileParser::ExNContext *ctx) = 0;
  virtual void exitExN(WhileParser::ExNContext *ctx) = 0;

  virtual void enterExArray(WhileParser::ExArrayContext *ctx) = 0;
  virtual void exitExArray(WhileParser::ExArrayContext *ctx) = 0;

  virtual void enterExArrayAddr(WhileParser::ExArrayAddrContext *ctx) = 0;
  virtual void exitExArrayAddr(WhileParser::ExArrayAddrContext *ctx) = 0;

  virtual void enterExAddr(WhileParser::ExAddrContext *ctx) = 0;
  virtual void exitExAddr(WhileParser::ExAddrContext *ctx) = 0;

  virtual void enterExMinus(WhileParser::ExMinusContext *ctx) = 0;
  virtual void exitExMinus(WhileParser::ExMinusContext *ctx) = 0;

  virtual void enterExMult(WhileParser::ExMultContext *ctx) = 0;
  virtual void exitExMult(WhileParser::ExMultContext *ctx) = 0;

  virtual void enterExDiv(WhileParser::ExDivContext *ctx) = 0;
  virtual void exitExDiv(WhileParser::ExDivContext *ctx) = 0;

  virtual void enterExPtr(WhileParser::ExPtrContext *ctx) = 0;
  virtual void exitExPtr(WhileParser::ExPtrContext *ctx) = 0;

  virtual void enterStmtsThen(WhileParser::StmtsThenContext *ctx) = 0;
  virtual void exitStmtsThen(WhileParser::StmtsThenContext *ctx) = 0;

  virtual void enterStmtsElse(WhileParser::StmtsElseContext *ctx) = 0;
  virtual void exitStmtsElse(WhileParser::StmtsElseContext *ctx) = 0;

  virtual void enterStmtsWhile(WhileParser::StmtsWhileContext *ctx) = 0;
  virtual void exitStmtsWhile(WhileParser::StmtsWhileContext *ctx) = 0;

  virtual void enterStmtVar(WhileParser::StmtVarContext *ctx) = 0;
  virtual void exitStmtVar(WhileParser::StmtVarContext *ctx) = 0;

  virtual void enterStmtAssign(WhileParser::StmtAssignContext *ctx) = 0;
  virtual void exitStmtAssign(WhileParser::StmtAssignContext *ctx) = 0;

  virtual void enterStmtArrayAssign(WhileParser::StmtArrayAssignContext *ctx) = 0;
  virtual void exitStmtArrayAssign(WhileParser::StmtArrayAssignContext *ctx) = 0;

  virtual void enterStmtPtrAssign(WhileParser::StmtPtrAssignContext *ctx) = 0;
  virtual void exitStmtPtrAssign(WhileParser::StmtPtrAssignContext *ctx) = 0;

  virtual void enterStmtExpr(WhileParser::StmtExprContext *ctx) = 0;
  virtual void exitStmtExpr(WhileParser::StmtExprContext *ctx) = 0;

  virtual void enterStmtIf(WhileParser::StmtIfContext *ctx) = 0;
  virtual void exitStmtIf(WhileParser::StmtIfContext *ctx) = 0;

  virtual void enterStmtWhile(WhileParser::StmtWhileContext *ctx) = 0;
  virtual void exitStmtWhile(WhileParser::StmtWhileContext *ctx) = 0;

  virtual void enterStmtReturn(WhileParser::StmtReturnContext *ctx) = 0;
  virtual void exitStmtReturn(WhileParser::StmtReturnContext *ctx) = 0;

  virtual void enterFun_body(WhileParser::Fun_bodyContext *ctx) = 0;
  virtual void exitFun_body(WhileParser::Fun_bodyContext *ctx) = 0;

  virtual void enterParameters(WhileParser::ParametersContext *ctx) = 0;
  virtual void exitParameters(WhileParser::ParametersContext *ctx) = 0;

  virtual void enterFun_def(WhileParser::Fun_defContext *ctx) = 0;
  virtual void exitFun_def(WhileParser::Fun_defContext *ctx) = 0;

  virtual void enterVar(WhileParser::VarContext *ctx) = 0;
  virtual void exitVar(WhileParser::VarContext *ctx) = 0;

  virtual void enterFun(WhileParser::FunContext *ctx) = 0;
  virtual void exitFun(WhileParser::FunContext *ctx) = 0;


};

