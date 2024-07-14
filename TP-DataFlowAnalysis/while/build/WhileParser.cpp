
#include <iostream>
#include <list>

#include "WhileLang.h"
#include "WhileCFG.h"


// Generated from /cal/exterieurs/benmbarek-23/Desktop/TP/S2/SE206/youssef-ben-mbarek/TP1/while/src/While.g4 by ANTLR 4.7.2


#include "WhileListener.h"

#include "WhileParser.h"


using namespace antlrcpp;
using namespace antlr4;

WhileParser::WhileParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

WhileParser::~WhileParser() {
  delete _interpreter;
}

std::string WhileParser::getGrammarFileName() const {
  return "While.g4";
}

const std::vector<std::string>& WhileParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& WhileParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

WhileParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WhileParser::ProgramContext::EOF() {
  return getToken(WhileParser::EOF, 0);
}

std::vector<WhileParser::DefinitionContext *> WhileParser::ProgramContext::definition() {
  return getRuleContexts<WhileParser::DefinitionContext>();
}

WhileParser::DefinitionContext* WhileParser::ProgramContext::definition(size_t i) {
  return getRuleContext<WhileParser::DefinitionContext>(i);
}


size_t WhileParser::ProgramContext::getRuleIndex() const {
  return WhileParser::RuleProgram;
}

void WhileParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void WhileParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

WhileParser::ProgramContext* WhileParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, WhileParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    defaultFunctions();
    setState(34);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WhileParser::T__0

    || _la == WhileParser::T__26) {
      setState(31);
      definition();
      setState(36);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(37);
    match(WhileParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Param_declContext ------------------------------------------------------------------

WhileParser::Param_declContext::Param_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WhileParser::Param_declContext::ID() {
  return getToken(WhileParser::ID, 0);
}

tree::TerminalNode* WhileParser::Param_declContext::N() {
  return getToken(WhileParser::N, 0);
}


size_t WhileParser::Param_declContext::getRuleIndex() const {
  return WhileParser::RuleParam_decl;
}

void WhileParser::Param_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_decl(this);
}

void WhileParser::Param_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_decl(this);
}

WhileParser::Param_declContext* WhileParser::param_decl() {
  Param_declContext *_localctx = _tracker.createInstance<Param_declContext>(_ctx, getState());
  enterRule(_localctx, 2, WhileParser::RuleParam_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(52);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(39);
      match(WhileParser::T__0);
      setState(40);
      dynamic_cast<Param_declContext *>(_localctx)->idToken = match(WhileParser::ID);
      Functions.back().Parameters.Symbols.emplace_back((dynamic_cast<Param_declContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Param_declContext *>(_localctx)->idToken->getText() : ""), WINT, 1, Functions.back().Parameters.Size++);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(42);
      match(WhileParser::T__0);
      setState(43);
      dynamic_cast<Param_declContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(44);
      match(WhileParser::T__1);
      setState(45);
      dynamic_cast<Param_declContext *>(_localctx)->nToken = match(WhileParser::N);
      setState(46);
      match(WhileParser::T__2);
      Functions.back().Parameters.Symbols.emplace_back((dynamic_cast<Param_declContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Param_declContext *>(_localctx)->idToken->getText() : ""), WARY, (dynamic_cast<Param_declContext *>(_localctx)->nToken != nullptr ? std::stoi(dynamic_cast<Param_declContext *>(_localctx)->nToken->getText()) : 0), Functions.back().Parameters.Size); Functions.back().Parameters.Size+=(dynamic_cast<Param_declContext *>(_localctx)->nToken != nullptr ? std::stoi(dynamic_cast<Param_declContext *>(_localctx)->nToken->getText()) : 0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(48);
      match(WhileParser::T__0);
      setState(49);
      match(WhileParser::T__3);
      setState(50);
      dynamic_cast<Param_declContext *>(_localctx)->idToken = match(WhileParser::ID);
      Functions.back().Parameters.Symbols.emplace_back((dynamic_cast<Param_declContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Param_declContext *>(_localctx)->idToken->getText() : ""), WPTR, 1, Functions.back().Parameters.Size++);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Int_initContext ------------------------------------------------------------------

WhileParser::Int_initContext::Int_initContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WhileParser::Int_initContext::Int_initContext(ParserRuleContext *parent, size_t invokingState, WhileSymbol * Sym)
  : ParserRuleContext(parent, invokingState) {
  this->Sym = Sym;
}

tree::TerminalNode* WhileParser::Int_initContext::N() {
  return getToken(WhileParser::N, 0);
}


size_t WhileParser::Int_initContext::getRuleIndex() const {
  return WhileParser::RuleInt_init;
}

void WhileParser::Int_initContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt_init(this);
}

void WhileParser::Int_initContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt_init(this);
}

WhileParser::Int_initContext* WhileParser::int_init(WhileSymbol * Sym) {
  Int_initContext *_localctx = _tracker.createInstance<Int_initContext>(_ctx, getState(), Sym);
  enterRule(_localctx, 4, WhileParser::RuleInt_init);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    match(WhileParser::T__4);
    setState(55);
    dynamic_cast<Int_initContext *>(_localctx)->nToken = match(WhileParser::N);
    _localctx->Sym->Init.emplace_back((dynamic_cast<Int_initContext *>(_localctx)->nToken != nullptr ? std::stoi(dynamic_cast<Int_initContext *>(_localctx)->nToken->getText()) : 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_initContext ------------------------------------------------------------------

WhileParser::Array_initContext::Array_initContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WhileParser::Array_initContext::Array_initContext(ParserRuleContext *parent, size_t invokingState, WhileSymbol * Sym)
  : ParserRuleContext(parent, invokingState) {
  this->Sym = Sym;
}

std::vector<tree::TerminalNode *> WhileParser::Array_initContext::N() {
  return getTokens(WhileParser::N);
}

tree::TerminalNode* WhileParser::Array_initContext::N(size_t i) {
  return getToken(WhileParser::N, i);
}

tree::TerminalNode* WhileParser::Array_initContext::S() {
  return getToken(WhileParser::S, 0);
}


size_t WhileParser::Array_initContext::getRuleIndex() const {
  return WhileParser::RuleArray_init;
}

void WhileParser::Array_initContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray_init(this);
}

void WhileParser::Array_initContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray_init(this);
}

WhileParser::Array_initContext* WhileParser::array_init(WhileSymbol * Sym) {
  Array_initContext *_localctx = _tracker.createInstance<Array_initContext>(_ctx, getState(), Sym);
  enterRule(_localctx, 6, WhileParser::RuleArray_init);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(74);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(58);
      match(WhileParser::T__4);
      setState(59);
      match(WhileParser::T__5);
      setState(60);
      dynamic_cast<Array_initContext *>(_localctx)->v1 = match(WhileParser::N);
      _localctx->Sym->Init.emplace_back((dynamic_cast<Array_initContext *>(_localctx)->v1 != nullptr ? std::stoi(dynamic_cast<Array_initContext *>(_localctx)->v1->getText()) : 0));
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == WhileParser::T__6) {
        setState(62);
        match(WhileParser::T__6);
        setState(63);
        dynamic_cast<Array_initContext *>(_localctx)->vn = match(WhileParser::N);
        _localctx->Sym->Init.emplace_back((dynamic_cast<Array_initContext *>(_localctx)->vn != nullptr ? std::stoi(dynamic_cast<Array_initContext *>(_localctx)->vn->getText()) : 0));
        setState(69);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(70);
      match(WhileParser::T__7);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(71);
      match(WhileParser::T__4);
      setState(72);
      dynamic_cast<Array_initContext *>(_localctx)->sToken = match(WhileParser::S);
      initStringSymbol((dynamic_cast<Array_initContext *>(_localctx)->sToken != nullptr ? dynamic_cast<Array_initContext *>(_localctx)->sToken->getText() : ""), _localctx->Sym);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_defContext ------------------------------------------------------------------

WhileParser::Var_defContext::Var_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WhileParser::Var_defContext::Var_defContext(ParserRuleContext *parent, size_t invokingState, WhileScope * Scope)
  : ParserRuleContext(parent, invokingState) {
  this->Scope = Scope;
}

tree::TerminalNode* WhileParser::Var_defContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::Int_initContext* WhileParser::Var_defContext::int_init() {
  return getRuleContext<WhileParser::Int_initContext>(0);
}

tree::TerminalNode* WhileParser::Var_defContext::N() {
  return getToken(WhileParser::N, 0);
}

WhileParser::Array_initContext* WhileParser::Var_defContext::array_init() {
  return getRuleContext<WhileParser::Array_initContext>(0);
}


size_t WhileParser::Var_defContext::getRuleIndex() const {
  return WhileParser::RuleVar_def;
}

void WhileParser::Var_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_def(this);
}

void WhileParser::Var_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_def(this);
}

WhileParser::Var_defContext* WhileParser::var_def(WhileScope * Scope) {
  Var_defContext *_localctx = _tracker.createInstance<Var_defContext>(_ctx, getState(), Scope);
  enterRule(_localctx, 8, WhileParser::RuleVar_def);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(105);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(76);
      match(WhileParser::T__0);
      setState(77);
      dynamic_cast<Var_defContext *>(_localctx)->idToken = match(WhileParser::ID);
      Scope->Symbols.emplace_back((dynamic_cast<Var_defContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Var_defContext *>(_localctx)->idToken->getText() : ""), WINT, 1, Scope->Size++); dynamic_cast<Var_defContext *>(_localctx)->Sym = &Scope->Symbols.back();
      setState(80);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WhileParser::T__4) {
        setState(79);
        int_init(_localctx->Sym);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(82);
      match(WhileParser::T__0);
      setState(83);
      dynamic_cast<Var_defContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(84);
      match(WhileParser::T__1);
      setState(85);
      dynamic_cast<Var_defContext *>(_localctx)->nToken = match(WhileParser::N);
      setState(86);
      match(WhileParser::T__2);
      Scope->Symbols.emplace_back((dynamic_cast<Var_defContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Var_defContext *>(_localctx)->idToken->getText() : ""), WARY, (dynamic_cast<Var_defContext *>(_localctx)->nToken != nullptr ? std::stoi(dynamic_cast<Var_defContext *>(_localctx)->nToken->getText()) : 0), Scope->Size); Scope->Size += (dynamic_cast<Var_defContext *>(_localctx)->nToken != nullptr ? std::stoi(dynamic_cast<Var_defContext *>(_localctx)->nToken->getText()) : 0); dynamic_cast<Var_defContext *>(_localctx)->Sym = &Scope->Symbols.back();
      setState(89);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WhileParser::T__4) {
        setState(88);
        array_init(_localctx->Sym);
      }
      checkArrayInit(_localctx->Sym, dynamic_cast<Var_defContext *>(_localctx)->idToken);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(92);
      match(WhileParser::T__0);
      setState(93);
      dynamic_cast<Var_defContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(94);
      match(WhileParser::T__1);
      setState(95);
      match(WhileParser::T__2);
      Scope->Symbols.emplace_back((dynamic_cast<Var_defContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Var_defContext *>(_localctx)->idToken->getText() : ""), WARY, 0, Scope->Size); dynamic_cast<Var_defContext *>(_localctx)->Sym = &Scope->Symbols.back();
      setState(98);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WhileParser::T__4) {
        setState(97);
        array_init(_localctx->Sym);
      }
      _localctx->Sym->Size = _localctx->Sym->Init.size(); ;Scope->Size += _localctx->Sym->Size; 
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(101);
      match(WhileParser::T__0);
      setState(102);
      match(WhileParser::T__3);
      setState(103);
      dynamic_cast<Var_defContext *>(_localctx)->idToken = match(WhileParser::ID);
      Scope->Symbols.emplace_back((dynamic_cast<Var_defContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Var_defContext *>(_localctx)->idToken->getText() : ""), WPTR, 1, Scope->Size++); dynamic_cast<Var_defContext *>(_localctx)->Sym = &Scope->Symbols.back();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Call_argsContext ------------------------------------------------------------------

WhileParser::Call_argsContext::Call_argsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WhileParser::ExprContext *> WhileParser::Call_argsContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::Call_argsContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}


size_t WhileParser::Call_argsContext::getRuleIndex() const {
  return WhileParser::RuleCall_args;
}

void WhileParser::Call_argsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall_args(this);
}

void WhileParser::Call_argsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall_args(this);
}

WhileParser::Call_argsContext* WhileParser::call_args() {
  Call_argsContext *_localctx = _tracker.createInstance<Call_argsContext>(_ctx, getState());
  enterRule(_localctx, 10, WhileParser::RuleCall_args);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WhileParser::T__3:
      case WhileParser::T__8:
      case WhileParser::T__10:
      case WhileParser::ID:
      case WhileParser::N: {
        enterOuterAlt(_localctx, 1);
        setState(107);
        dynamic_cast<Call_argsContext *>(_localctx)->exprContext = expr(0);
        dynamic_cast<Call_argsContext *>(_localctx)->a.push_back(dynamic_cast<Call_argsContext *>(_localctx)->exprContext);
        setState(112);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == WhileParser::T__6) {
          setState(108);
          match(WhileParser::T__6);
          setState(109);
          dynamic_cast<Call_argsContext *>(_localctx)->exprContext = expr(0);
          dynamic_cast<Call_argsContext *>(_localctx)->a.push_back(dynamic_cast<Call_argsContext *>(_localctx)->exprContext);
          setState(114);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        dynamic_cast<Call_argsContext *>(_localctx)->args =  dynamic_cast<Call_argsContext *>(_localctx)->a;
        break;
      }

      case WhileParser::T__9: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

WhileParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t WhileParser::ExprContext::getRuleIndex() const {
  return WhileParser::RuleExpr;
}

void WhileParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
  this->Ty = ctx->Ty;
}

//----------------- ExUnequalContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExUnequalContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExUnequalContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExUnequalContext::ExUnequalContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExUnequalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExUnequal(this);
}
void WhileParser::ExUnequalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExUnequal(this);
}
//----------------- ExCallContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::ExCallContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::Call_argsContext* WhileParser::ExCallContext::call_args() {
  return getRuleContext<WhileParser::Call_argsContext>(0);
}

WhileParser::ExCallContext::ExCallContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExCall(this);
}
void WhileParser::ExCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExCall(this);
}
//----------------- ExLessEqualContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExLessEqualContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExLessEqualContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExLessEqualContext::ExLessEqualContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExLessEqualContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExLessEqual(this);
}
void WhileParser::ExLessEqualContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExLessEqual(this);
}
//----------------- ExIDContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::ExIDContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::ExIDContext::ExIDContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExIDContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExID(this);
}
void WhileParser::ExIDContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExID(this);
}
//----------------- ExLessContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExLessContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExLessContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExLessContext::ExLessContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExLessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExLess(this);
}
void WhileParser::ExLessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExLess(this);
}
//----------------- ExExprContext ------------------------------------------------------------------

WhileParser::ExprContext* WhileParser::ExExprContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::ExExprContext::ExExprContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExExpr(this);
}
void WhileParser::ExExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExExpr(this);
}
//----------------- ExPlusContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExPlusContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExPlusContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExPlusContext::ExPlusContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExPlusContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExPlus(this);
}
void WhileParser::ExPlusContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExPlus(this);
}
//----------------- ExEqualContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExEqualContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExEqualContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExEqualContext::ExEqualContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExEqualContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExEqual(this);
}
void WhileParser::ExEqualContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExEqual(this);
}
//----------------- ExNContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::ExNContext::N() {
  return getToken(WhileParser::N, 0);
}

WhileParser::ExNContext::ExNContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExNContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExN(this);
}
void WhileParser::ExNContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExN(this);
}
//----------------- ExArrayContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::ExArrayContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::ExprContext* WhileParser::ExArrayContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::ExArrayContext::ExArrayContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExArray(this);
}
void WhileParser::ExArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExArray(this);
}
//----------------- ExArrayAddrContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::ExArrayAddrContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::ExprContext* WhileParser::ExArrayAddrContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::ExArrayAddrContext::ExArrayAddrContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExArrayAddrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExArrayAddr(this);
}
void WhileParser::ExArrayAddrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExArrayAddr(this);
}
//----------------- ExAddrContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::ExAddrContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::ExAddrContext::ExAddrContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExAddrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExAddr(this);
}
void WhileParser::ExAddrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExAddr(this);
}
//----------------- ExMinusContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExMinusContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExMinusContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExMinusContext::ExMinusContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExMinusContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExMinus(this);
}
void WhileParser::ExMinusContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExMinus(this);
}
//----------------- ExMultContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExMultContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExMultContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExMultContext::ExMultContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExMultContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExMult(this);
}
void WhileParser::ExMultContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExMult(this);
}
//----------------- ExDivContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::ExDivContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::ExDivContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::ExDivContext::ExDivContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExDivContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExDiv(this);
}
void WhileParser::ExDivContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExDiv(this);
}
//----------------- ExPtrContext ------------------------------------------------------------------

WhileParser::ExprContext* WhileParser::ExPtrContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::ExPtrContext::ExPtrContext(ExprContext *ctx) { copyFrom(ctx); }

void WhileParser::ExPtrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExPtr(this);
}
void WhileParser::ExPtrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExPtr(this);
}

WhileParser::ExprContext* WhileParser::expr() {
   return expr(0);
}

WhileParser::ExprContext* WhileParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WhileParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  WhileParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, WhileParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(157);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ExNContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(121);
      match(WhileParser::N);
      dynamic_cast<ExNContext *>(_localctx)->Ty =  WINT;
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ExIDContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(123);
      dynamic_cast<ExIDContext *>(_localctx)->idToken = match(WhileParser::ID);
      dynamic_cast<ExIDContext *>(_localctx)->Ty =  typeOfVariable(dynamic_cast<ExIDContext *>(_localctx)->idToken);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ExArrayContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(125);
      dynamic_cast<ExArrayContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(126);
      dynamic_cast<ExArrayContext *>(_localctx)->op = match(WhileParser::T__1);
      setState(127);
      dynamic_cast<ExArrayContext *>(_localctx)->exprContext = expr(0);
      setState(128);
      match(WhileParser::T__2);
      dynamic_cast<ExArrayContext *>(_localctx)->Ty =  typeOfArray(typeOfVariable(dynamic_cast<ExArrayContext *>(_localctx)->idToken), dynamic_cast<ExArrayContext *>(_localctx)->exprContext->Ty, dynamic_cast<ExArrayContext *>(_localctx)->op);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ExCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(131);
      dynamic_cast<ExCallContext *>(_localctx)->idToken = match(WhileParser::ID);

      setState(132);
      match(WhileParser::T__8);
      setState(133);
      dynamic_cast<ExCallContext *>(_localctx)->call_argsContext = call_args();
      setState(134);
      match(WhileParser::T__9);
      dynamic_cast<ExCallContext *>(_localctx)->Ty =  typeOfFunction(dynamic_cast<ExCallContext *>(_localctx)->idToken, dynamic_cast<ExCallContext *>(_localctx)->call_argsContext->args);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ExAddrContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(138);
      match(WhileParser::T__10);
      setState(139);
      dynamic_cast<ExAddrContext *>(_localctx)->idToken = match(WhileParser::ID);
      dynamic_cast<ExAddrContext *>(_localctx)->Ty =  WPTR; typeOfInt(typeOfVariable(dynamic_cast<ExAddrContext *>(_localctx)->idToken, true), dynamic_cast<ExAddrContext *>(_localctx)->idToken);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ExArrayAddrContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(141);
      match(WhileParser::T__10);
      setState(142);
      dynamic_cast<ExArrayAddrContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(143);
      dynamic_cast<ExArrayAddrContext *>(_localctx)->op = match(WhileParser::T__1);
      setState(144);
      dynamic_cast<ExArrayAddrContext *>(_localctx)->r = dynamic_cast<ExArrayAddrContext *>(_localctx)->exprContext = expr(0);
      setState(145);
      match(WhileParser::T__2);
      dynamic_cast<ExArrayAddrContext *>(_localctx)->Ty =  WPTR; typeOfArray(typeOfVariable(dynamic_cast<ExArrayAddrContext *>(_localctx)->idToken, true), dynamic_cast<ExArrayAddrContext *>(_localctx)->r->Ty, dynamic_cast<ExArrayAddrContext *>(_localctx)->op);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ExPtrContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(148);
      dynamic_cast<ExPtrContext *>(_localctx)->op = match(WhileParser::T__3);
      setState(149);
      dynamic_cast<ExPtrContext *>(_localctx)->exprContext = expr(10);
      dynamic_cast<ExPtrContext *>(_localctx)->Ty =  typeOfPtr(dynamic_cast<ExPtrContext *>(_localctx)->exprContext->Ty, dynamic_cast<ExPtrContext *>(_localctx)->op);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ExExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(152);
      match(WhileParser::T__8);
      setState(153);
      dynamic_cast<ExExprContext *>(_localctx)->exprContext = expr(0);
      setState(154);
      match(WhileParser::T__9);
      dynamic_cast<ExExprContext *>(_localctx)->Ty =  dynamic_cast<ExExprContext *>(_localctx)->exprContext->Ty;
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(201);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(199);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ExEqualContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(159);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(160);
          dynamic_cast<ExEqualContext *>(_localctx)->op = match(WhileParser::T__11);
          setState(161);
          dynamic_cast<ExEqualContext *>(_localctx)->r = dynamic_cast<ExEqualContext *>(_localctx)->exprContext = expr(10);
          dynamic_cast<ExEqualContext *>(_localctx)->Ty =  WINT; typeOfBinary(dynamic_cast<ExEqualContext *>(_localctx)->l->Ty, dynamic_cast<ExEqualContext *>(_localctx)->r->Ty, dynamic_cast<ExEqualContext *>(_localctx)->op);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ExUnequalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(164);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(165);
          dynamic_cast<ExUnequalContext *>(_localctx)->op = match(WhileParser::T__12);
          setState(166);
          dynamic_cast<ExUnequalContext *>(_localctx)->r = dynamic_cast<ExUnequalContext *>(_localctx)->exprContext = expr(9);
          dynamic_cast<ExUnequalContext *>(_localctx)->Ty =  WINT; typeOfBinary(dynamic_cast<ExUnequalContext *>(_localctx)->l->Ty, dynamic_cast<ExUnequalContext *>(_localctx)->r->Ty, dynamic_cast<ExUnequalContext *>(_localctx)->op);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ExLessContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(169);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(170);
          dynamic_cast<ExLessContext *>(_localctx)->op = match(WhileParser::T__13);
          setState(171);
          dynamic_cast<ExLessContext *>(_localctx)->r = dynamic_cast<ExLessContext *>(_localctx)->exprContext = expr(8);
          dynamic_cast<ExLessContext *>(_localctx)->Ty =  WINT; typeOfBinary(dynamic_cast<ExLessContext *>(_localctx)->l->Ty, dynamic_cast<ExLessContext *>(_localctx)->r->Ty, dynamic_cast<ExLessContext *>(_localctx)->op);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ExLessEqualContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(174);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(175);
          dynamic_cast<ExLessEqualContext *>(_localctx)->op = match(WhileParser::T__14);
          setState(176);
          dynamic_cast<ExLessEqualContext *>(_localctx)->r = dynamic_cast<ExLessEqualContext *>(_localctx)->exprContext = expr(7);
          dynamic_cast<ExLessEqualContext *>(_localctx)->Ty =  WINT; typeOfBinary(dynamic_cast<ExLessEqualContext *>(_localctx)->l->Ty, dynamic_cast<ExLessEqualContext *>(_localctx)->r->Ty, dynamic_cast<ExLessEqualContext *>(_localctx)->op);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<ExMultContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(179);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(180);
          dynamic_cast<ExMultContext *>(_localctx)->op = match(WhileParser::T__3);
          setState(181);
          dynamic_cast<ExMultContext *>(_localctx)->r = dynamic_cast<ExMultContext *>(_localctx)->exprContext = expr(6);
          dynamic_cast<ExMultContext *>(_localctx)->Ty =  typeOfBinary(dynamic_cast<ExMultContext *>(_localctx)->l->Ty, dynamic_cast<ExMultContext *>(_localctx)->r->Ty, dynamic_cast<ExMultContext *>(_localctx)->op);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<ExDivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(184);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(185);
          dynamic_cast<ExDivContext *>(_localctx)->op = match(WhileParser::T__15);
          setState(186);
          dynamic_cast<ExDivContext *>(_localctx)->r = dynamic_cast<ExDivContext *>(_localctx)->exprContext = expr(5);
          dynamic_cast<ExDivContext *>(_localctx)->Ty =  typeOfBinary(dynamic_cast<ExDivContext *>(_localctx)->l->Ty, dynamic_cast<ExDivContext *>(_localctx)->r->Ty, dynamic_cast<ExDivContext *>(_localctx)->op);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<ExPlusContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(189);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(190);
          dynamic_cast<ExPlusContext *>(_localctx)->op = match(WhileParser::T__16);
          setState(191);
          dynamic_cast<ExPlusContext *>(_localctx)->r = dynamic_cast<ExPlusContext *>(_localctx)->exprContext = expr(4);
          dynamic_cast<ExPlusContext *>(_localctx)->Ty =  typeOfPlus(dynamic_cast<ExPlusContext *>(_localctx)->l->Ty, dynamic_cast<ExPlusContext *>(_localctx)->r->Ty, dynamic_cast<ExPlusContext *>(_localctx)->op);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ExMinusContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->l = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(194);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(195);
          dynamic_cast<ExMinusContext *>(_localctx)->op = match(WhileParser::T__17);
          setState(196);
          dynamic_cast<ExMinusContext *>(_localctx)->r = dynamic_cast<ExMinusContext *>(_localctx)->exprContext = expr(3);
          dynamic_cast<ExMinusContext *>(_localctx)->Ty =  typeOfPlus(dynamic_cast<ExMinusContext *>(_localctx)->l->Ty, dynamic_cast<ExMinusContext *>(_localctx)->r->Ty, dynamic_cast<ExMinusContext *>(_localctx)->op);
          break;
        }

        } 
      }
      setState(203);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StmtsThenContext ------------------------------------------------------------------

WhileParser::StmtsThenContext::StmtsThenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WhileParser::StatementContext *> WhileParser::StmtsThenContext::statement() {
  return getRuleContexts<WhileParser::StatementContext>();
}

WhileParser::StatementContext* WhileParser::StmtsThenContext::statement(size_t i) {
  return getRuleContext<WhileParser::StatementContext>(i);
}


size_t WhileParser::StmtsThenContext::getRuleIndex() const {
  return WhileParser::RuleStmtsThen;
}

void WhileParser::StmtsThenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtsThen(this);
}

void WhileParser::StmtsThenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtsThen(this);
}

WhileParser::StmtsThenContext* WhileParser::stmtsThen() {
  StmtsThenContext *_localctx = _tracker.createInstance<StmtsThenContext>(_ctx, getState());
  enterRule(_localctx, 14, WhileParser::RuleStmtsThen);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WhileParser::T__0)
      | (1ULL << WhileParser::T__3)
      | (1ULL << WhileParser::T__8)
      | (1ULL << WhileParser::T__10)
      | (1ULL << WhileParser::T__19)
      | (1ULL << WhileParser::T__23)
      | (1ULL << WhileParser::T__25)
      | (1ULL << WhileParser::ID)
      | (1ULL << WhileParser::N))) != 0)) {
      setState(204);
      statement();
      setState(205);
      match(WhileParser::T__18);
      setState(211);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtsElseContext ------------------------------------------------------------------

WhileParser::StmtsElseContext::StmtsElseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WhileParser::StatementContext *> WhileParser::StmtsElseContext::statement() {
  return getRuleContexts<WhileParser::StatementContext>();
}

WhileParser::StatementContext* WhileParser::StmtsElseContext::statement(size_t i) {
  return getRuleContext<WhileParser::StatementContext>(i);
}


size_t WhileParser::StmtsElseContext::getRuleIndex() const {
  return WhileParser::RuleStmtsElse;
}

void WhileParser::StmtsElseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtsElse(this);
}

void WhileParser::StmtsElseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtsElse(this);
}

WhileParser::StmtsElseContext* WhileParser::stmtsElse() {
  StmtsElseContext *_localctx = _tracker.createInstance<StmtsElseContext>(_ctx, getState());
  enterRule(_localctx, 16, WhileParser::RuleStmtsElse);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WhileParser::T__0)
      | (1ULL << WhileParser::T__3)
      | (1ULL << WhileParser::T__8)
      | (1ULL << WhileParser::T__10)
      | (1ULL << WhileParser::T__19)
      | (1ULL << WhileParser::T__23)
      | (1ULL << WhileParser::T__25)
      | (1ULL << WhileParser::ID)
      | (1ULL << WhileParser::N))) != 0)) {
      setState(212);
      statement();
      setState(213);
      match(WhileParser::T__18);
      setState(219);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtsWhileContext ------------------------------------------------------------------

WhileParser::StmtsWhileContext::StmtsWhileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WhileParser::StatementContext *> WhileParser::StmtsWhileContext::statement() {
  return getRuleContexts<WhileParser::StatementContext>();
}

WhileParser::StatementContext* WhileParser::StmtsWhileContext::statement(size_t i) {
  return getRuleContext<WhileParser::StatementContext>(i);
}


size_t WhileParser::StmtsWhileContext::getRuleIndex() const {
  return WhileParser::RuleStmtsWhile;
}

void WhileParser::StmtsWhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtsWhile(this);
}

void WhileParser::StmtsWhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtsWhile(this);
}

WhileParser::StmtsWhileContext* WhileParser::stmtsWhile() {
  StmtsWhileContext *_localctx = _tracker.createInstance<StmtsWhileContext>(_ctx, getState());
  enterRule(_localctx, 18, WhileParser::RuleStmtsWhile);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WhileParser::T__0)
      | (1ULL << WhileParser::T__3)
      | (1ULL << WhileParser::T__8)
      | (1ULL << WhileParser::T__10)
      | (1ULL << WhileParser::T__19)
      | (1ULL << WhileParser::T__23)
      | (1ULL << WhileParser::T__25)
      | (1ULL << WhileParser::ID)
      | (1ULL << WhileParser::N))) != 0)) {
      setState(220);
      statement();
      setState(221);
      match(WhileParser::T__18);
      setState(227);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

WhileParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t WhileParser::StatementContext::getRuleIndex() const {
  return WhileParser::RuleStatement;
}

void WhileParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
  this->BBStmt = ctx->BBStmt;
}

//----------------- StmtReturnContext ------------------------------------------------------------------

WhileParser::ExprContext* WhileParser::StmtReturnContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::StmtReturnContext::StmtReturnContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtReturnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtReturn(this);
}
void WhileParser::StmtReturnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtReturn(this);
}
//----------------- StmtVarContext ------------------------------------------------------------------

WhileParser::Var_defContext* WhileParser::StmtVarContext::var_def() {
  return getRuleContext<WhileParser::Var_defContext>(0);
}

WhileParser::StmtVarContext::StmtVarContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtVarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtVar(this);
}
void WhileParser::StmtVarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtVar(this);
}
//----------------- StmtArrayAssignContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::StmtArrayAssignContext::ID() {
  return getToken(WhileParser::ID, 0);
}

std::vector<WhileParser::ExprContext *> WhileParser::StmtArrayAssignContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::StmtArrayAssignContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::StmtArrayAssignContext::StmtArrayAssignContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtArrayAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtArrayAssign(this);
}
void WhileParser::StmtArrayAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtArrayAssign(this);
}
//----------------- StmtExprContext ------------------------------------------------------------------

WhileParser::ExprContext* WhileParser::StmtExprContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::StmtExprContext::StmtExprContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtExpr(this);
}
void WhileParser::StmtExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtExpr(this);
}
//----------------- StmtWhileContext ------------------------------------------------------------------

WhileParser::ExprContext* WhileParser::StmtWhileContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::StmtsWhileContext* WhileParser::StmtWhileContext::stmtsWhile() {
  return getRuleContext<WhileParser::StmtsWhileContext>(0);
}

WhileParser::StmtWhileContext::StmtWhileContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtWhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtWhile(this);
}
void WhileParser::StmtWhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtWhile(this);
}
//----------------- StmtAssignContext ------------------------------------------------------------------

tree::TerminalNode* WhileParser::StmtAssignContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::ExprContext* WhileParser::StmtAssignContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::StmtAssignContext::StmtAssignContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtAssign(this);
}
void WhileParser::StmtAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtAssign(this);
}
//----------------- StmtPtrAssignContext ------------------------------------------------------------------

std::vector<WhileParser::ExprContext *> WhileParser::StmtPtrAssignContext::expr() {
  return getRuleContexts<WhileParser::ExprContext>();
}

WhileParser::ExprContext* WhileParser::StmtPtrAssignContext::expr(size_t i) {
  return getRuleContext<WhileParser::ExprContext>(i);
}

WhileParser::StmtPtrAssignContext::StmtPtrAssignContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtPtrAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtPtrAssign(this);
}
void WhileParser::StmtPtrAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtPtrAssign(this);
}
//----------------- StmtIfContext ------------------------------------------------------------------

WhileParser::ExprContext* WhileParser::StmtIfContext::expr() {
  return getRuleContext<WhileParser::ExprContext>(0);
}

WhileParser::StmtsThenContext* WhileParser::StmtIfContext::stmtsThen() {
  return getRuleContext<WhileParser::StmtsThenContext>(0);
}

WhileParser::StmtsElseContext* WhileParser::StmtIfContext::stmtsElse() {
  return getRuleContext<WhileParser::StmtsElseContext>(0);
}

WhileParser::StmtIfContext::StmtIfContext(StatementContext *ctx) { copyFrom(ctx); }

void WhileParser::StmtIfContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtIf(this);
}
void WhileParser::StmtIfContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtIf(this);
}
WhileParser::StatementContext* WhileParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 20, WhileParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(274);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtVarContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(228);
      var_def(&Functions.back().Locals);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtAssignContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(229);
      dynamic_cast<StmtAssignContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(230);
      dynamic_cast<StmtAssignContext *>(_localctx)->op = match(WhileParser::T__4);
      setState(231);
      dynamic_cast<StmtAssignContext *>(_localctx)->exprContext = expr(0);
      typeOfBinary(typeOfVariable(dynamic_cast<StmtAssignContext *>(_localctx)->idToken), dynamic_cast<StmtAssignContext *>(_localctx)->exprContext->Ty, dynamic_cast<StmtAssignContext *>(_localctx)->op);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtArrayAssignContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(234);
      dynamic_cast<StmtArrayAssignContext *>(_localctx)->idToken = match(WhileParser::ID);
      setState(239);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WhileParser::T__1) {
        setState(235);
        match(WhileParser::T__1);
        setState(236);
        dynamic_cast<StmtArrayAssignContext *>(_localctx)->i = expr(0);
        setState(237);
        match(WhileParser::T__2);
      }
      setState(241);
      dynamic_cast<StmtArrayAssignContext *>(_localctx)->op = match(WhileParser::T__4);
      setState(242);
      dynamic_cast<StmtArrayAssignContext *>(_localctx)->r = expr(0);
      typeOfArrayAssign(dynamic_cast<StmtArrayAssignContext *>(_localctx)->idToken, dynamic_cast<StmtArrayAssignContext *>(_localctx)->i->Ty, dynamic_cast<StmtArrayAssignContext *>(_localctx)->r->Ty, dynamic_cast<StmtArrayAssignContext *>(_localctx)->op);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtPtrAssignContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(245);
      match(WhileParser::T__3);
      setState(246);
      dynamic_cast<StmtPtrAssignContext *>(_localctx)->l = expr(0);
      setState(247);
      dynamic_cast<StmtPtrAssignContext *>(_localctx)->op = match(WhileParser::T__4);
      setState(248);
      dynamic_cast<StmtPtrAssignContext *>(_localctx)->r = expr(0);
      typeOfPtrAssign(dynamic_cast<StmtPtrAssignContext *>(_localctx)->l->Ty, dynamic_cast<StmtPtrAssignContext *>(_localctx)->r->Ty, dynamic_cast<StmtPtrAssignContext *>(_localctx)->op);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtExprContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(251);
      expr(0);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtIfContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(252);
      dynamic_cast<StmtIfContext *>(_localctx)->op = match(WhileParser::T__19);
      setState(253);
      dynamic_cast<StmtIfContext *>(_localctx)->exprContext = expr(0);
      setState(254);
      match(WhileParser::T__20);
      typeOfInt(dynamic_cast<StmtIfContext *>(_localctx)->exprContext->Ty, dynamic_cast<StmtIfContext *>(_localctx)->op);
      setState(256);
      stmtsThen();
      setState(259);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WhileParser::T__21) {
        setState(257);
        match(WhileParser::T__21);
        setState(258);
        stmtsElse();
      }
      setState(261);
      match(WhileParser::T__22);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtWhileContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(263);
      dynamic_cast<StmtWhileContext *>(_localctx)->op = match(WhileParser::T__23);
      setState(264);
      dynamic_cast<StmtWhileContext *>(_localctx)->exprContext = expr(0);
      setState(265);
      match(WhileParser::T__24);
      typeOfInt(dynamic_cast<StmtWhileContext *>(_localctx)->exprContext->Ty, dynamic_cast<StmtWhileContext *>(_localctx)->op);
      setState(267);
      stmtsWhile();
      setState(268);
      match(WhileParser::T__22);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<WhileParser::StmtReturnContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(270);
      dynamic_cast<StmtReturnContext *>(_localctx)->op = match(WhileParser::T__25);
      setState(271);
      dynamic_cast<StmtReturnContext *>(_localctx)->exprContext = expr(0);
      typeOfReturn(dynamic_cast<StmtReturnContext *>(_localctx)->exprContext->Ty, dynamic_cast<StmtReturnContext *>(_localctx)->op);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fun_bodyContext ------------------------------------------------------------------

WhileParser::Fun_bodyContext::Fun_bodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WhileParser::StatementContext *> WhileParser::Fun_bodyContext::statement() {
  return getRuleContexts<WhileParser::StatementContext>();
}

WhileParser::StatementContext* WhileParser::Fun_bodyContext::statement(size_t i) {
  return getRuleContext<WhileParser::StatementContext>(i);
}


size_t WhileParser::Fun_bodyContext::getRuleIndex() const {
  return WhileParser::RuleFun_body;
}

void WhileParser::Fun_bodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFun_body(this);
}

void WhileParser::Fun_bodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFun_body(this);
}

WhileParser::Fun_bodyContext* WhileParser::fun_body() {
  Fun_bodyContext *_localctx = _tracker.createInstance<Fun_bodyContext>(_ctx, getState());
  enterRule(_localctx, 22, WhileParser::RuleFun_body);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WhileParser::T__0)
      | (1ULL << WhileParser::T__3)
      | (1ULL << WhileParser::T__8)
      | (1ULL << WhileParser::T__10)
      | (1ULL << WhileParser::T__19)
      | (1ULL << WhileParser::T__23)
      | (1ULL << WhileParser::T__25)
      | (1ULL << WhileParser::ID)
      | (1ULL << WhileParser::N))) != 0)) {
      setState(276);
      statement();
      setState(277);
      match(WhileParser::T__18);
      setState(283);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

WhileParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WhileParser::Param_declContext *> WhileParser::ParametersContext::param_decl() {
  return getRuleContexts<WhileParser::Param_declContext>();
}

WhileParser::Param_declContext* WhileParser::ParametersContext::param_decl(size_t i) {
  return getRuleContext<WhileParser::Param_declContext>(i);
}


size_t WhileParser::ParametersContext::getRuleIndex() const {
  return WhileParser::RuleParameters;
}

void WhileParser::ParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameters(this);
}

void WhileParser::ParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameters(this);
}

WhileParser::ParametersContext* WhileParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 24, WhileParser::RuleParameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    match(WhileParser::T__8);
    setState(285);
    param_decl();
    setState(290);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WhileParser::T__6) {
      setState(286);
      match(WhileParser::T__6);
      setState(287);
      param_decl();
      setState(292);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(293);
    match(WhileParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fun_defContext ------------------------------------------------------------------

WhileParser::Fun_defContext::Fun_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WhileParser::Fun_defContext::ID() {
  return getToken(WhileParser::ID, 0);
}

WhileParser::Fun_bodyContext* WhileParser::Fun_defContext::fun_body() {
  return getRuleContext<WhileParser::Fun_bodyContext>(0);
}

WhileParser::ParametersContext* WhileParser::Fun_defContext::parameters() {
  return getRuleContext<WhileParser::ParametersContext>(0);
}


size_t WhileParser::Fun_defContext::getRuleIndex() const {
  return WhileParser::RuleFun_def;
}

void WhileParser::Fun_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFun_def(this);
}

void WhileParser::Fun_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFun_def(this);
}

WhileParser::Fun_defContext* WhileParser::fun_def() {
  Fun_defContext *_localctx = _tracker.createInstance<Fun_defContext>(_ctx, getState());
  enterRule(_localctx, 26, WhileParser::RuleFun_def);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(WhileParser::T__26);
    setState(298);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WhileParser::T__3) {
      dynamic_cast<Fun_defContext *>(_localctx)->Ty =  WPTR;
      setState(297);
      match(WhileParser::T__3);
    }
    setState(300);
    dynamic_cast<Fun_defContext *>(_localctx)->idToken = match(WhileParser::ID);
    Functions.emplace_back((dynamic_cast<Fun_defContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Fun_defContext *>(_localctx)->idToken->getText() : ""), _localctx->Ty); dynamic_cast<Fun_defContext *>(_localctx)->Fun =  &Functions.back();
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WhileParser::T__8) {
      setState(302);
      parameters();
    }
    setState(305);
    match(WhileParser::T__27);
    _localctx->Fun->Locals.Size = _localctx->Fun->Parameters.Size;
    setState(307);
    fun_body();
    setState(308);
    match(WhileParser::T__22);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefinitionContext ------------------------------------------------------------------

WhileParser::DefinitionContext::DefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t WhileParser::DefinitionContext::getRuleIndex() const {
  return WhileParser::RuleDefinition;
}

void WhileParser::DefinitionContext::copyFrom(DefinitionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- VarContext ------------------------------------------------------------------

WhileParser::Var_defContext* WhileParser::VarContext::var_def() {
  return getRuleContext<WhileParser::Var_defContext>(0);
}

WhileParser::VarContext::VarContext(DefinitionContext *ctx) { copyFrom(ctx); }

void WhileParser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}
void WhileParser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}
//----------------- FunContext ------------------------------------------------------------------

WhileParser::Fun_defContext* WhileParser::FunContext::fun_def() {
  return getRuleContext<WhileParser::Fun_defContext>(0);
}

WhileParser::FunContext::FunContext(DefinitionContext *ctx) { copyFrom(ctx); }

void WhileParser::FunContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFun(this);
}
void WhileParser::FunContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<WhileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFun(this);
}
WhileParser::DefinitionContext* WhileParser::definition() {
  DefinitionContext *_localctx = _tracker.createInstance<DefinitionContext>(_ctx, getState());
  enterRule(_localctx, 28, WhileParser::RuleDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(314);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WhileParser::T__0: {
        _localctx = dynamic_cast<DefinitionContext *>(_tracker.createInstance<WhileParser::VarContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(310);
        var_def(&Globals);
        setState(311);
        match(WhileParser::T__18);
        break;
      }

      case WhileParser::T__26: {
        _localctx = dynamic_cast<DefinitionContext *>(_tracker.createInstance<WhileParser::FunContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(313);
        fun_def();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool WhileParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool WhileParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 9);
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);
    case 7: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> WhileParser::_decisionToDFA;
atn::PredictionContextCache WhileParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN WhileParser::_atn;
std::vector<uint16_t> WhileParser::_serializedATN;

std::vector<std::string> WhileParser::_ruleNames = {
  "program", "param_decl", "int_init", "array_init", "var_def", "call_args", 
  "expr", "stmtsThen", "stmtsElse", "stmtsWhile", "statement", "fun_body", 
  "parameters", "fun_def", "definition"
};

std::vector<std::string> WhileParser::_literalNames = {
  "", "'int'", "'['", "']'", "'*'", "'='", "'{'", "','", "'}'", "'('", "')'", 
  "'&'", "'=='", "'!='", "'<'", "'<='", "'/'", "'+'", "'-'", "';'", "'if'", 
  "'then'", "'else'", "'end'", "'while'", "'do'", "'return'", "'fun'", "'begin'"
};

std::vector<std::string> WhileParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "WS", "COMMENT", "ID", "N", 
  "S"
};

dfa::Vocabulary WhileParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> WhileParser::_tokenNames;

WhileParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x23, 0x13f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 
    0x23, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x26, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 
    0x37, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x44, 
    0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x47, 0xb, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0x4d, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x5, 0x6, 0x53, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x5c, 0xa, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0x65, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 
    0x6, 0x6c, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x71, 0xa, 
    0x7, 0xc, 0x7, 0xe, 0x7, 0x74, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x5, 0x7, 0x79, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0xa0, 0xa, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0xca, 0xa, 
    0x8, 0xc, 0x8, 0xe, 0x8, 0xcd, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x7, 0x9, 0xd2, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xd5, 0xb, 0x9, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0xda, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xdd, 
    0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xe2, 0xa, 0xb, 0xc, 
    0xb, 0xe, 0xb, 0xe5, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x5, 0xc, 0xf2, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 
    0xc, 0x106, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x5, 0xc, 0x115, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 
    0xd, 0x11a, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x11d, 0xb, 0xd, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x123, 0xa, 0xe, 0xc, 0xe, 0xe, 
    0xe, 0x126, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 
    0x5, 0xf, 0x12d, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x132, 
    0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x13d, 0xa, 0x10, 0x3, 0x10, 
    0x2, 0x3, 0xe, 0x11, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
    0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x2, 0x2, 0x2, 0x15c, 0x2, 0x20, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x36, 0x3, 0x2, 0x2, 0x2, 0x6, 0x38, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x4c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x78, 0x3, 0x2, 0x2, 0x2, 0xe, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0xd3, 0x3, 0x2, 0x2, 0x2, 0x12, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x14, 0xe3, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x114, 0x3, 0x2, 0x2, 0x2, 0x18, 0x11b, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x129, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x20, 0x24, 0x8, 0x2, 0x1, 
    0x2, 0x21, 0x23, 0x5, 0x1e, 0x10, 0x2, 0x22, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x23, 0x26, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x27, 0x3, 0x2, 0x2, 0x2, 0x26, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x7, 0x2, 0x2, 0x3, 0x28, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x3, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0x21, 
    0x2, 0x2, 0x2b, 0x37, 0x8, 0x3, 0x1, 0x2, 0x2c, 0x2d, 0x7, 0x3, 0x2, 
    0x2, 0x2d, 0x2e, 0x7, 0x21, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x4, 0x2, 0x2, 
    0x2f, 0x30, 0x7, 0x22, 0x2, 0x2, 0x30, 0x31, 0x7, 0x5, 0x2, 0x2, 0x31, 
    0x37, 0x8, 0x3, 0x1, 0x2, 0x32, 0x33, 0x7, 0x3, 0x2, 0x2, 0x33, 0x34, 
    0x7, 0x6, 0x2, 0x2, 0x34, 0x35, 0x7, 0x21, 0x2, 0x2, 0x35, 0x37, 0x8, 
    0x3, 0x1, 0x2, 0x36, 0x29, 0x3, 0x2, 0x2, 0x2, 0x36, 0x2c, 0x3, 0x2, 
    0x2, 0x2, 0x36, 0x32, 0x3, 0x2, 0x2, 0x2, 0x37, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x39, 0x7, 0x7, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x22, 0x2, 0x2, 
    0x3a, 0x3b, 0x8, 0x4, 0x1, 0x2, 0x3b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x3d, 0x7, 0x7, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x8, 0x2, 0x2, 0x3e, 0x3f, 
    0x7, 0x22, 0x2, 0x2, 0x3f, 0x45, 0x8, 0x5, 0x1, 0x2, 0x40, 0x41, 0x7, 
    0x9, 0x2, 0x2, 0x41, 0x42, 0x7, 0x22, 0x2, 0x2, 0x42, 0x44, 0x8, 0x5, 
    0x1, 0x2, 0x43, 0x40, 0x3, 0x2, 0x2, 0x2, 0x44, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x48, 0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x4d, 0x7, 0xa, 0x2, 0x2, 0x49, 0x4a, 0x7, 0x7, 0x2, 0x2, 0x4a, 0x4b, 
    0x7, 0x23, 0x2, 0x2, 0x4b, 0x4d, 0x8, 0x5, 0x1, 0x2, 0x4c, 0x3c, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x21, 0x2, 
    0x2, 0x50, 0x52, 0x8, 0x6, 0x1, 0x2, 0x51, 0x53, 0x5, 0x6, 0x4, 0x2, 
    0x52, 0x51, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 0x53, 
    0x6c, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0x3, 0x2, 0x2, 0x55, 0x56, 
    0x7, 0x21, 0x2, 0x2, 0x56, 0x57, 0x7, 0x4, 0x2, 0x2, 0x57, 0x58, 0x7, 
    0x22, 0x2, 0x2, 0x58, 0x59, 0x7, 0x5, 0x2, 0x2, 0x59, 0x5b, 0x8, 0x6, 
    0x1, 0x2, 0x5a, 0x5c, 0x5, 0x8, 0x5, 0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 
    0x2, 0x5b, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x5d, 0x6c, 0x8, 0x6, 0x1, 0x2, 0x5e, 0x5f, 0x7, 0x3, 0x2, 0x2, 0x5f, 
    0x60, 0x7, 0x21, 0x2, 0x2, 0x60, 0x61, 0x7, 0x4, 0x2, 0x2, 0x61, 0x62, 
    0x7, 0x5, 0x2, 0x2, 0x62, 0x64, 0x8, 0x6, 0x1, 0x2, 0x63, 0x65, 0x5, 
    0x8, 0x5, 0x2, 0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x3, 0x2, 
    0x2, 0x2, 0x65, 0x66, 0x3, 0x2, 0x2, 0x2, 0x66, 0x6c, 0x8, 0x6, 0x1, 
    0x2, 0x67, 0x68, 0x7, 0x3, 0x2, 0x2, 0x68, 0x69, 0x7, 0x6, 0x2, 0x2, 
    0x69, 0x6a, 0x7, 0x21, 0x2, 0x2, 0x6a, 0x6c, 0x8, 0x6, 0x1, 0x2, 0x6b, 
    0x4e, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x54, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x5e, 
    0x3, 0x2, 0x2, 0x2, 0x6b, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6c, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x6d, 0x72, 0x5, 0xe, 0x8, 0x2, 0x6e, 0x6f, 0x7, 0x9, 
    0x2, 0x2, 0x6f, 0x71, 0x5, 0xe, 0x8, 0x2, 0x70, 0x6e, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x74, 0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 
    0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 0x73, 0x75, 0x3, 0x2, 0x2, 0x2, 0x74, 
    0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x8, 0x7, 0x1, 0x2, 0x76, 0x79, 
    0x3, 0x2, 0x2, 0x2, 0x77, 0x79, 0x3, 0x2, 0x2, 0x2, 0x78, 0x6d, 0x3, 
    0x2, 0x2, 0x2, 0x78, 0x77, 0x3, 0x2, 0x2, 0x2, 0x79, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0x7a, 0x7b, 0x8, 0x8, 0x1, 0x2, 0x7b, 0x7c, 0x7, 0x22, 0x2, 
    0x2, 0x7c, 0xa0, 0x8, 0x8, 0x1, 0x2, 0x7d, 0x7e, 0x7, 0x21, 0x2, 0x2, 
    0x7e, 0xa0, 0x8, 0x8, 0x1, 0x2, 0x7f, 0x80, 0x7, 0x21, 0x2, 0x2, 0x80, 
    0x81, 0x7, 0x4, 0x2, 0x2, 0x81, 0x82, 0x5, 0xe, 0x8, 0x2, 0x82, 0x83, 
    0x7, 0x5, 0x2, 0x2, 0x83, 0x84, 0x8, 0x8, 0x1, 0x2, 0x84, 0xa0, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x86, 0x7, 0x21, 0x2, 0x2, 0x86, 0x87, 0x7, 0xb, 
    0x2, 0x2, 0x87, 0x88, 0x5, 0xc, 0x7, 0x2, 0x88, 0x89, 0x7, 0xc, 0x2, 
    0x2, 0x89, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x8, 0x8, 0x1, 0x2, 
    0x8b, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0xd, 0x2, 0x2, 0x8d, 
    0x8e, 0x7, 0x21, 0x2, 0x2, 0x8e, 0xa0, 0x8, 0x8, 0x1, 0x2, 0x8f, 0x90, 
    0x7, 0xd, 0x2, 0x2, 0x90, 0x91, 0x7, 0x21, 0x2, 0x2, 0x91, 0x92, 0x7, 
    0x4, 0x2, 0x2, 0x92, 0x93, 0x5, 0xe, 0x8, 0x2, 0x93, 0x94, 0x7, 0x5, 
    0x2, 0x2, 0x94, 0x95, 0x8, 0x8, 0x1, 0x2, 0x95, 0xa0, 0x3, 0x2, 0x2, 
    0x2, 0x96, 0x97, 0x7, 0x6, 0x2, 0x2, 0x97, 0x98, 0x5, 0xe, 0x8, 0xc, 
    0x98, 0x99, 0x8, 0x8, 0x1, 0x2, 0x99, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9a, 
    0x9b, 0x7, 0xb, 0x2, 0x2, 0x9b, 0x9c, 0x5, 0xe, 0x8, 0x2, 0x9c, 0x9d, 
    0x7, 0xc, 0x2, 0x2, 0x9d, 0x9e, 0x8, 0x8, 0x1, 0x2, 0x9e, 0xa0, 0x3, 
    0x2, 0x2, 0x2, 0x9f, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x7d, 0x3, 0x2, 
    0x2, 0x2, 0x9f, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x9f, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x8f, 0x3, 0x2, 0x2, 0x2, 
    0x9f, 0x96, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x9a, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0xcb, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0xc, 0xb, 0x2, 0x2, 0xa2, 0xa3, 
    0x7, 0xe, 0x2, 0x2, 0xa3, 0xa4, 0x5, 0xe, 0x8, 0xc, 0xa4, 0xa5, 0x8, 
    0x8, 0x1, 0x2, 0xa5, 0xca, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0xc, 0xa, 
    0x2, 0x2, 0xa7, 0xa8, 0x7, 0xf, 0x2, 0x2, 0xa8, 0xa9, 0x5, 0xe, 0x8, 
    0xb, 0xa9, 0xaa, 0x8, 0x8, 0x1, 0x2, 0xaa, 0xca, 0x3, 0x2, 0x2, 0x2, 
    0xab, 0xac, 0xc, 0x9, 0x2, 0x2, 0xac, 0xad, 0x7, 0x10, 0x2, 0x2, 0xad, 
    0xae, 0x5, 0xe, 0x8, 0xa, 0xae, 0xaf, 0x8, 0x8, 0x1, 0x2, 0xaf, 0xca, 
    0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0xc, 0x8, 0x2, 0x2, 0xb1, 0xb2, 0x7, 
    0x11, 0x2, 0x2, 0xb2, 0xb3, 0x5, 0xe, 0x8, 0x9, 0xb3, 0xb4, 0x8, 0x8, 
    0x1, 0x2, 0xb4, 0xca, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0xc, 0x7, 0x2, 
    0x2, 0xb6, 0xb7, 0x7, 0x6, 0x2, 0x2, 0xb7, 0xb8, 0x5, 0xe, 0x8, 0x8, 
    0xb8, 0xb9, 0x8, 0x8, 0x1, 0x2, 0xb9, 0xca, 0x3, 0x2, 0x2, 0x2, 0xba, 
    0xbb, 0xc, 0x6, 0x2, 0x2, 0xbb, 0xbc, 0x7, 0x12, 0x2, 0x2, 0xbc, 0xbd, 
    0x5, 0xe, 0x8, 0x7, 0xbd, 0xbe, 0x8, 0x8, 0x1, 0x2, 0xbe, 0xca, 0x3, 
    0x2, 0x2, 0x2, 0xbf, 0xc0, 0xc, 0x5, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x13, 
    0x2, 0x2, 0xc1, 0xc2, 0x5, 0xe, 0x8, 0x6, 0xc2, 0xc3, 0x8, 0x8, 0x1, 
    0x2, 0xc3, 0xca, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0xc, 0x4, 0x2, 0x2, 
    0xc5, 0xc6, 0x7, 0x14, 0x2, 0x2, 0xc6, 0xc7, 0x5, 0xe, 0x8, 0x5, 0xc7, 
    0xc8, 0x8, 0x8, 0x1, 0x2, 0xc8, 0xca, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xa1, 
    0x3, 0x2, 0x2, 0x2, 0xc9, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xab, 0x3, 
    0x2, 0x2, 0x2, 0xc9, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xb5, 0x3, 0x2, 
    0x2, 0x2, 0xc9, 0xba, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xbf, 0x3, 0x2, 0x2, 
    0x2, 0xc9, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcd, 0x3, 0x2, 0x2, 0x2, 
    0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcc, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 
    0x5, 0x16, 0xc, 0x2, 0xcf, 0xd0, 0x7, 0x15, 0x2, 0x2, 0xd0, 0xd2, 0x3, 
    0x2, 0x2, 0x2, 0xd1, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd5, 0x3, 0x2, 
    0x2, 0x2, 0xd3, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x3, 0x2, 0x2, 
    0x2, 0xd4, 0x11, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0xd6, 0xd7, 0x5, 0x16, 0xc, 0x2, 0xd7, 0xd8, 0x7, 0x15, 0x2, 0x2, 0xd8, 
    0xda, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdd, 
    0x3, 0x2, 0x2, 0x2, 0xdb, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xdc, 0x13, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xdb, 0x3, 0x2, 
    0x2, 0x2, 0xde, 0xdf, 0x5, 0x16, 0xc, 0x2, 0xdf, 0xe0, 0x7, 0x15, 0x2, 
    0x2, 0xe0, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xde, 0x3, 0x2, 0x2, 0x2, 
    0xe2, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0xe4, 0x3, 0x2, 0x2, 0x2, 0xe4, 0x15, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe3, 
    0x3, 0x2, 0x2, 0x2, 0xe6, 0x115, 0x5, 0xa, 0x6, 0x2, 0xe7, 0xe8, 0x7, 
    0x21, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0x7, 0x2, 0x2, 0xe9, 0xea, 0x5, 0xe, 
    0x8, 0x2, 0xea, 0xeb, 0x8, 0xc, 0x1, 0x2, 0xeb, 0x115, 0x3, 0x2, 0x2, 
    0x2, 0xec, 0xf1, 0x7, 0x21, 0x2, 0x2, 0xed, 0xee, 0x7, 0x4, 0x2, 0x2, 
    0xee, 0xef, 0x5, 0xe, 0x8, 0x2, 0xef, 0xf0, 0x7, 0x5, 0x2, 0x2, 0xf0, 
    0xf2, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xed, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 
    0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf4, 0x7, 
    0x7, 0x2, 0x2, 0xf4, 0xf5, 0x5, 0xe, 0x8, 0x2, 0xf5, 0xf6, 0x8, 0xc, 
    0x1, 0x2, 0xf6, 0x115, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf8, 0x7, 0x6, 0x2, 
    0x2, 0xf8, 0xf9, 0x5, 0xe, 0x8, 0x2, 0xf9, 0xfa, 0x7, 0x7, 0x2, 0x2, 
    0xfa, 0xfb, 0x5, 0xe, 0x8, 0x2, 0xfb, 0xfc, 0x8, 0xc, 0x1, 0x2, 0xfc, 
    0x115, 0x3, 0x2, 0x2, 0x2, 0xfd, 0x115, 0x5, 0xe, 0x8, 0x2, 0xfe, 0xff, 
    0x7, 0x16, 0x2, 0x2, 0xff, 0x100, 0x5, 0xe, 0x8, 0x2, 0x100, 0x101, 
    0x7, 0x17, 0x2, 0x2, 0x101, 0x102, 0x8, 0xc, 0x1, 0x2, 0x102, 0x105, 
    0x5, 0x10, 0x9, 0x2, 0x103, 0x104, 0x7, 0x18, 0x2, 0x2, 0x104, 0x106, 
    0x5, 0x12, 0xa, 0x2, 0x105, 0x103, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 
    0x3, 0x2, 0x2, 0x2, 0x106, 0x107, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 
    0x7, 0x19, 0x2, 0x2, 0x108, 0x115, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 
    0x7, 0x1a, 0x2, 0x2, 0x10a, 0x10b, 0x5, 0xe, 0x8, 0x2, 0x10b, 0x10c, 
    0x7, 0x1b, 0x2, 0x2, 0x10c, 0x10d, 0x8, 0xc, 0x1, 0x2, 0x10d, 0x10e, 
    0x5, 0x14, 0xb, 0x2, 0x10e, 0x10f, 0x7, 0x19, 0x2, 0x2, 0x10f, 0x115, 
    0x3, 0x2, 0x2, 0x2, 0x110, 0x111, 0x7, 0x1c, 0x2, 0x2, 0x111, 0x112, 
    0x5, 0xe, 0x8, 0x2, 0x112, 0x113, 0x8, 0xc, 0x1, 0x2, 0x113, 0x115, 
    0x3, 0x2, 0x2, 0x2, 0x114, 0xe6, 0x3, 0x2, 0x2, 0x2, 0x114, 0xe7, 0x3, 
    0x2, 0x2, 0x2, 0x114, 0xec, 0x3, 0x2, 0x2, 0x2, 0x114, 0xf7, 0x3, 0x2, 
    0x2, 0x2, 0x114, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x114, 0xfe, 0x3, 0x2, 0x2, 
    0x2, 0x114, 0x109, 0x3, 0x2, 0x2, 0x2, 0x114, 0x110, 0x3, 0x2, 0x2, 
    0x2, 0x115, 0x17, 0x3, 0x2, 0x2, 0x2, 0x116, 0x117, 0x5, 0x16, 0xc, 
    0x2, 0x117, 0x118, 0x7, 0x15, 0x2, 0x2, 0x118, 0x11a, 0x3, 0x2, 0x2, 
    0x2, 0x119, 0x116, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11d, 0x3, 0x2, 0x2, 
    0x2, 0x11b, 0x119, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0x3, 0x2, 0x2, 
    0x2, 0x11c, 0x19, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11b, 0x3, 0x2, 0x2, 0x2, 
    0x11e, 0x11f, 0x7, 0xb, 0x2, 0x2, 0x11f, 0x124, 0x5, 0x4, 0x3, 0x2, 
    0x120, 0x121, 0x7, 0x9, 0x2, 0x2, 0x121, 0x123, 0x5, 0x4, 0x3, 0x2, 
    0x122, 0x120, 0x3, 0x2, 0x2, 0x2, 0x123, 0x126, 0x3, 0x2, 0x2, 0x2, 
    0x124, 0x122, 0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 
    0x125, 0x127, 0x3, 0x2, 0x2, 0x2, 0x126, 0x124, 0x3, 0x2, 0x2, 0x2, 
    0x127, 0x128, 0x7, 0xc, 0x2, 0x2, 0x128, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x129, 
    0x12c, 0x7, 0x1d, 0x2, 0x2, 0x12a, 0x12b, 0x8, 0xf, 0x1, 0x2, 0x12b, 
    0x12d, 0x7, 0x6, 0x2, 0x2, 0x12c, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12c, 
    0x12d, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x12e, 
    0x12f, 0x7, 0x21, 0x2, 0x2, 0x12f, 0x131, 0x8, 0xf, 0x1, 0x2, 0x130, 
    0x132, 0x5, 0x1a, 0xe, 0x2, 0x131, 0x130, 0x3, 0x2, 0x2, 0x2, 0x131, 
    0x132, 0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 0x3, 0x2, 0x2, 0x2, 0x133, 
    0x134, 0x7, 0x1e, 0x2, 0x2, 0x134, 0x135, 0x8, 0xf, 0x1, 0x2, 0x135, 
    0x136, 0x5, 0x18, 0xd, 0x2, 0x136, 0x137, 0x7, 0x19, 0x2, 0x2, 0x137, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 0x5, 0xa, 0x6, 0x2, 0x139, 0x13a, 
    0x7, 0x15, 0x2, 0x2, 0x13a, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13d, 
    0x5, 0x1c, 0xf, 0x2, 0x13c, 0x138, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13b, 
    0x3, 0x2, 0x2, 0x2, 0x13d, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x24, 0x36, 
    0x45, 0x4c, 0x52, 0x5b, 0x64, 0x6b, 0x72, 0x78, 0x9f, 0xc9, 0xcb, 0xd3, 
    0xdb, 0xe3, 0xf1, 0x105, 0x114, 0x11b, 0x124, 0x12c, 0x131, 0x13c, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

WhileParser::Initializer WhileParser::_init;
