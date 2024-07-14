
#include <iostream>
#include <list>

#include "WhileLang.h"
#include "WhileCFG.h"


// Generated from /cal/exterieurs/benmbarek-23/Desktop/TP/S2/SE206/youssef-ben-mbarek/TP1/while/src/While.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  WhileParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, WS = 29, COMMENT = 30, ID = 31, N = 32, S = 33
  };

  enum {
    RuleProgram = 0, RuleParam_decl = 1, RuleInt_init = 2, RuleArray_init = 3, 
    RuleVar_def = 4, RuleCall_args = 5, RuleExpr = 6, RuleStmtsThen = 7, 
    RuleStmtsElse = 8, RuleStmtsWhile = 9, RuleStatement = 10, RuleFun_body = 11, 
    RuleParameters = 12, RuleFun_def = 13, RuleDefinition = 14
  };

  WhileParser(antlr4::TokenStream *input);
  ~WhileParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


    class ExprContext;
    std::list<WhileFunctionSymbol> Functions;
    WhileScope Globals;

    bool Error = false;

    std::ostream &error(antlr4::Token *token)
    {
      Error = true;
      if (token)
      {
        std::cerr << "line " << token->getLine()
                  << ":" << token->getCharPositionInLine() << " ";
      }
      return std::cerr;
    }

    template<typename T>
    T *findSymbol(const std::string &name, std::list<T> &scope) const
    {
      for(auto b = scope.rbegin(), e = scope.rend(); b != e; b++)
      {
        if (b->Name == name)
          return &*b;
      }

      return nullptr;
    }

    WhileType typeOfFunction(antlr4::Token *token, std::vector<ExprContext*> args)
    {
      std::string name = token->getText();
      WhileFunctionSymbol *fun = findSymbol(name, Functions);

      if (fun)
      {
        if (fun->Parameters.Symbols.size() != args.size())
        {
          error(token) << "mismatch in number of function arguments, expected "
                       << fun->Parameters.Symbols.size() << " argument(s).\n";
        }

        auto j(args.begin());
        for(auto i(fun->Parameters.Symbols.begin());
            i != fun->Parameters.Symbols.end(); i++, j++)
        {
          if (i->Type != (*j)->Ty)
            error((*j)->getStart()) << "incompatible types, '"
                                    << WhileTypes[i->Type] << "' expected, got '"
                                    << WhileTypes[(*j)->Ty] << "'.\n";
        }

        return fun->Type;
      }
      else
      {
        error(token) << "invalid function reference '" << name << "'.\n";
        return WERR;
      }
    }

    WhileType typeOfVariable(antlr4::Token *token, bool addressTaken = false)
    {
      std::string name = token->getText();
      WhileSymbol *local = findSymbol(name, Functions.back().Locals.Symbols);
      WhileSymbol *param = findSymbol(name, Functions.back().Parameters.Symbols);
      WhileSymbol *global = findSymbol(name, Globals.Symbols);

      if (local)
      {
        local->AddressTaken |= addressTaken;
        return local->Type;
      }
      if (param)
      {
        param->AddressTaken |= addressTaken;
        return param->Type;
      }
      else if (global)
      {
        global->AddressTaken |= addressTaken;
        return global->Type;
      }
      else
      {
        error(token) << "invalid variable reference '" << name << "'.\n";
        return WERR;
      }
    }

    static bool isScalar(WhileType t)
    {
      return t == WINT || t == WPTR;
    }

    WhileType typeOfPlus(WhileType l, WhileType r, antlr4::Token *token)
    {
      if (l == r)
        return l;
      else if (l == WPTR && isScalar(r))
        return l;
      else if (r == WPTR && isScalar(l))
        return r;
      else
      {
        error(token) << "incompatible types for operator '" << token->getText()
                     << "', scalar types expected ('" << WhileTypes[WINT] << "', '"
                     << WhileTypes[WPTR] << "').\n";
        return WERR;
      }
    }

    WhileType typeOfBinary(WhileType l, WhileType r, antlr4::Token *token)
    {
      if (l == r && isScalar(l))
        return l;
      else
      {
        error(token) << "incompatible types for operator '" << token->getText()
                     << "', '" << WhileTypes[l] << "' does not match '"
                     << WhileTypes[r] << "'.\n";
        return WERR;
      }
    }

    WhileType typeOfArray(WhileType l, WhileType r, antlr4::Token *token)
    {
      if (l != WARY)
      {
        error(token) << "incompatible type, '" << WhileTypes[WARY]
                     << "' expected for array access, got '"
                     << WhileTypes[l] << "'.\n";
      }

      if (r != WINT)
      {
        error(token) << "incompatible type, '" << WhileTypes[WINT]
                     << "'  expected as index for array access, got '"
                     << WhileTypes[r] << "'.\n";
      }

      return WINT;
    }

    WhileType typeOfPtr(WhileType p, antlr4::Token *token)
    {
      if (p != WPTR)
      {
        error(token) << "incompatible type, '" << WhileTypes[WPTR]
                     << "' expected for pointer access, got '"
                     << WhileTypes[p] << "'.\n";
      }
      return WINT;
    }

    WhileType typeOfPtrAssign(WhileType l, WhileType r, antlr4::Token *token)
    {
      if (l != WPTR)
      {
        error(token) << "incompatible type, '" << WhileTypes[WPTR]
                     << "' expected for pointer access, got '"
                     << WhileTypes[l] << "'.\n";
      }
      if (r != WINT)
      {
        error(token) << "incompatible type, '" << WhileTypes[WINT]
                     << "' expected, got '"
                     << WhileTypes[r] << "'.\n";
      }

      return WINT;
    }

    WhileType typeOfArrayAssign(antlr4::Token *id, WhileType i, WhileType r,
                                antlr4::Token *token)
    {
      WhileType l = typeOfArray(typeOfVariable(id), i, token);
      return typeOfBinary(l, r, token);
    }


    void typeOfInt(WhileType c, antlr4::Token *token)
    {
      if (c != WINT)
      {
        error(token) << "incompatible type, '" << WhileTypes[WINT]
                     << "' expected, got '"
                     << WhileTypes[c] << "'.\n";
      }
    }

    void typeOfReturn(WhileType r, antlr4::Token *token)
    {
      if (r != Functions.back().Type)
      {
        error(token) << "incompatible return type, '"
                     << WhileTypes[Functions.back().Type] << "' expected, got '"
                     << WhileTypes[r] << "'\n";
      }
    }

    void checkArrayInit(WhileSymbol *sym, antlr4::Token *token)
    {
      if (sym->Size < sym->Init.size())
      {
        error(token) << "invalid array initializer, array size is '"
                     << sym->Size << ", got '" << sym->Init.size()
                     << "' values.\n";
      }
    }

    void defaultFunctions()
    {
      for(auto &[n,b] : WhileBuiltins)
      {
        Functions.emplace_back(n, WINT);
        WhileFunctionSymbol &f = Functions.back();
        for(WhileType t : b.ParameterTypes)
        {
          f.Parameters.Symbols.emplace_back("a", t, 1, f.Parameters.Size++);
        }
      }
    }

    void initStringSymbol(const std::string &str, WhileSymbol *sym)
    {
      for(char c : str.substr(1, str.size() - 2)+'\0')
        sym->Init.emplace_back(c);
    }


  class ProgramContext;
  class Param_declContext;
  class Int_initContext;
  class Array_initContext;
  class Var_defContext;
  class Call_argsContext;
  class ExprContext;
  class StmtsThenContext;
  class StmtsElseContext;
  class StmtsWhileContext;
  class StatementContext;
  class Fun_bodyContext;
  class ParametersContext;
  class Fun_defContext;
  class DefinitionContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DefinitionContext *> definition();
    DefinitionContext* definition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  Param_declContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *idToken = nullptr;;
    antlr4::Token *nToken = nullptr;;
    Param_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *N();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Param_declContext* param_decl();

  class  Int_initContext : public antlr4::ParserRuleContext {
  public:
    WhileSymbol * Sym;
    antlr4::Token *nToken = nullptr;;
    Int_initContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    Int_initContext(antlr4::ParserRuleContext *parent, size_t invokingState, WhileSymbol * Sym);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *N();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Int_initContext* int_init(WhileSymbol * Sym);

  class  Array_initContext : public antlr4::ParserRuleContext {
  public:
    WhileSymbol * Sym;
    antlr4::Token *v1 = nullptr;;
    antlr4::Token *vn = nullptr;;
    antlr4::Token *sToken = nullptr;;
    Array_initContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    Array_initContext(antlr4::ParserRuleContext *parent, size_t invokingState, WhileSymbol * Sym);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> N();
    antlr4::tree::TerminalNode* N(size_t i);
    antlr4::tree::TerminalNode *S();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Array_initContext* array_init(WhileSymbol * Sym);

  class  Var_defContext : public antlr4::ParserRuleContext {
  public:
    WhileScope * Scope;
    WhileSymbol * Sym;
    antlr4::Token *idToken = nullptr;;
    antlr4::Token *nToken = nullptr;;
    Var_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    Var_defContext(antlr4::ParserRuleContext *parent, size_t invokingState, WhileScope * Scope);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    Int_initContext *int_init();
    antlr4::tree::TerminalNode *N();
    Array_initContext *array_init();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Var_defContext* var_def(WhileScope * Scope);

  class  Call_argsContext : public antlr4::ParserRuleContext {
  public:
    std::vector<ExprContext*> args;
    WhileParser::ExprContext *exprContext = nullptr;;
    std::vector<ExprContext *> a;;
    Call_argsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Call_argsContext* call_args();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    WhileType Ty = WERR; WhileOperand Op;;
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExUnequalContext : public ExprContext {
  public:
    ExUnequalContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExCallContext : public ExprContext {
  public:
    ExCallContext(ExprContext *ctx);

    antlr4::Token *idToken = nullptr;
    WhileParser::Call_argsContext *call_argsContext = nullptr;
    antlr4::tree::TerminalNode *ID();
    Call_argsContext *call_args();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExLessEqualContext : public ExprContext {
  public:
    ExLessEqualContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExIDContext : public ExprContext {
  public:
    ExIDContext(ExprContext *ctx);

    antlr4::Token *idToken = nullptr;
    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExLessContext : public ExprContext {
  public:
    ExLessContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExExprContext : public ExprContext {
  public:
    ExExprContext(ExprContext *ctx);

    WhileParser::ExprContext *exprContext = nullptr;
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExPlusContext : public ExprContext {
  public:
    ExPlusContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExEqualContext : public ExprContext {
  public:
    ExEqualContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExNContext : public ExprContext {
  public:
    ExNContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *N();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExArrayContext : public ExprContext {
  public:
    ExArrayContext(ExprContext *ctx);

    antlr4::Token *idToken = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExArrayAddrContext : public ExprContext {
  public:
    ExArrayAddrContext(ExprContext *ctx);

    antlr4::Token *idToken = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExAddrContext : public ExprContext {
  public:
    ExAddrContext(ExprContext *ctx);

    antlr4::Token *idToken = nullptr;
    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExMinusContext : public ExprContext {
  public:
    ExMinusContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExMultContext : public ExprContext {
  public:
    ExMultContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExDivContext : public ExprContext {
  public:
    ExDivContext(ExprContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ExPtrContext : public ExprContext {
  public:
    ExPtrContext(ExprContext *ctx);

    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  StmtsThenContext : public antlr4::ParserRuleContext {
  public:
    WhileBlock * BBThenExit = nullptr;;
    StmtsThenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StmtsThenContext* stmtsThen();

  class  StmtsElseContext : public antlr4::ParserRuleContext {
  public:
    WhileBlock * BBElseEntry = nullptr;;
    StmtsElseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StmtsElseContext* stmtsElse();

  class  StmtsWhileContext : public antlr4::ParserRuleContext {
  public:
    StmtsWhileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StmtsWhileContext* stmtsWhile();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    WhileBlock * BBStmt = nullptr;;
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StmtReturnContext : public StatementContext {
  public:
    StmtReturnContext(StatementContext *ctx);

    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtVarContext : public StatementContext {
  public:
    StmtVarContext(StatementContext *ctx);

    Var_defContext *var_def();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtArrayAssignContext : public StatementContext {
  public:
    StmtArrayAssignContext(StatementContext *ctx);

    antlr4::Token *idToken = nullptr;
    WhileParser::ExprContext *i = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    antlr4::tree::TerminalNode *ID();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtExprContext : public StatementContext {
  public:
    StmtExprContext(StatementContext *ctx);

    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtWhileContext : public StatementContext {
  public:
    StmtWhileContext(StatementContext *ctx);

    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    ExprContext *expr();
    StmtsWhileContext *stmtsWhile();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtAssignContext : public StatementContext {
  public:
    StmtAssignContext(StatementContext *ctx);

    antlr4::Token *idToken = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    antlr4::tree::TerminalNode *ID();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtPtrAssignContext : public StatementContext {
  public:
    StmtPtrAssignContext(StatementContext *ctx);

    WhileParser::ExprContext *l = nullptr;
    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *r = nullptr;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  StmtIfContext : public StatementContext {
  public:
    StmtIfContext(StatementContext *ctx);

    antlr4::Token *op = nullptr;
    WhileParser::ExprContext *exprContext = nullptr;
    ExprContext *expr();
    StmtsThenContext *stmtsThen();
    StmtsElseContext *stmtsElse();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  StatementContext* statement();

  class  Fun_bodyContext : public antlr4::ParserRuleContext {
  public:
    Fun_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Fun_bodyContext* fun_body();

  class  ParametersContext : public antlr4::ParserRuleContext {
  public:
    ParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Param_declContext *> param_decl();
    Param_declContext* param_decl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParametersContext* parameters();

  class  Fun_defContext : public antlr4::ParserRuleContext {
  public:
    WhileFunctionSymbol * Fun = nullptr;;
    WhileType Ty = WINT;;
    antlr4::Token *idToken = nullptr;;
    Fun_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    Fun_bodyContext *fun_body();
    ParametersContext *parameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Fun_defContext* fun_def();

  class  DefinitionContext : public antlr4::ParserRuleContext {
  public:
    DefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DefinitionContext() = default;
    void copyFrom(DefinitionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  VarContext : public DefinitionContext {
  public:
    VarContext(DefinitionContext *ctx);

    Var_defContext *var_def();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FunContext : public DefinitionContext {
  public:
    FunContext(DefinitionContext *ctx);

    Fun_defContext *fun_def();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  DefinitionContext* definition();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

