// This file is part of While, an educational programming language and program
// analysis framework.
//
//   Copyright 2023 Florian Brandner
//
// While is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// While is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// While. If not, see <https://www.gnu.org/licenses/>.
//
// Contact: florian.brandner@telecom-paris.fr
//


// This file defines the grammar of the While language, along with some simple
// extensions for semantics/type checking.


// TODO:
// - prohibit negative symbol sizes
// - prohibit redefinition of symbols
grammar While;

@parser::header
{
#include <iostream>
#include <list>

#include "WhileLang.h"
#include "WhileCFG.h"
}

@parser::members
{
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
}

program
  : {defaultFunctions();} definition* EOF
  ;

// Lexer
WS
  : [ \t\n\r]+ -> channel(HIDDEN)
  ;

COMMENT
  : '//' ~[\r\n]* -> channel(HIDDEN)
  ;

ID
  : [a-zA-Z][a-zA-Z0-9_]*
  ;

N
  : '-'? [0-9]+
  ;

S
  : '"' ~["]* '"'
  ;

// Parser
param_decl
  : 'int' ID            {Functions.back().Parameters.Symbols.emplace_back($ID.text, WINT, 1, Functions.back().Parameters.Size++);}
  | 'int' ID '[' N ']'  {Functions.back().Parameters.Symbols.emplace_back($ID.text, WARY, $N.int, Functions.back().Parameters.Size); Functions.back().Parameters.Size+=$N.int;}
  | 'int' '*' ID        {Functions.back().Parameters.Symbols.emplace_back($ID.text, WPTR, 1, Functions.back().Parameters.Size++);}
  ;

int_init[WhileSymbol *Sym]
  : '=' N {$Sym->Init.emplace_back($N.int);}
  ;

array_init[WhileSymbol *Sym]
  : '=' '{' v1=N        {$Sym->Init.emplace_back($v1.int);}
    (','
      vn=N              {$Sym->Init.emplace_back($vn.int);}
    )* '}'
  | '=' S               {initStringSymbol($S.text, $Sym);}
  ;

var_def[WhileScope *Scope] returns[WhileSymbol *Sym]
  : 'int' ID                {Scope->Symbols.emplace_back($ID.text, WINT, 1, Scope->Size++); $Sym=&Scope->Symbols.back();}
    (int_init[$Sym])?
  | 'int' ID '[' N ']'      {Scope->Symbols.emplace_back($ID.text, WARY, $N.int, Scope->Size); Scope->Size += $N.int; $Sym=&Scope->Symbols.back();}
    (array_init[$Sym])?     {checkArrayInit($Sym, $ID);}
  | 'int' ID '[' ']'        {Scope->Symbols.emplace_back($ID.text, WARY, 0, Scope->Size); $Sym=&Scope->Symbols.back();}
    (array_init[$Sym])?     {$Sym->Size = $Sym->Init.size(); ;Scope->Size += $Sym->Size; }
  | 'int' '*' ID            {Scope->Symbols.emplace_back($ID.text, WPTR, 1, Scope->Size++); $Sym=&Scope->Symbols.back();}
  ;

call_args returns[std::vector<ExprContext*> args]
  : a+=expr (',' a+=expr)* {$args = $a;}
  |
  ;

expr returns[WhileType Ty = WERR; WhileOperand Op;]
  : N                          {$Ty = WINT;}                                                      #ExN
  | ID                         {$Ty = typeOfVariable($ID);}                                       #ExID
  | ID op='[' expr ']'         {$Ty = typeOfArray(typeOfVariable($ID), $expr.Ty, $op);}           #ExArray
  | ID ('(' call_args ')')     {$Ty = typeOfFunction($ID, $call_args.args);}                      #ExCall
  | '&' ID                     {$Ty = WPTR; typeOfInt(typeOfVariable($ID, true), $ID);}           #ExAddr
  | '&' ID op='[' r=expr ']'   {$Ty = WPTR; typeOfArray(typeOfVariable($ID, true), $r.Ty, $op);}  #ExArrayAddr
  | op='*' expr                {$Ty = typeOfPtr($expr.Ty, $op);}                                  #ExPtr
  | l=expr op='==' r=expr      {$Ty = WINT; typeOfBinary($l.Ty, $r.Ty, $op);}                     #ExEqual
  | l=expr op='!=' r=expr      {$Ty = WINT; typeOfBinary($l.Ty, $r.Ty, $op);}                     #ExUnequal
  | l=expr op='<' r=expr       {$Ty = WINT; typeOfBinary($l.Ty, $r.Ty, $op);}                     #ExLess
  | l=expr op='<=' r=expr      {$Ty = WINT; typeOfBinary($l.Ty, $r.Ty, $op);}                     #ExLessEqual
  | l=expr op='*' r=expr       {$Ty = typeOfBinary($l.Ty, $r.Ty, $op);}                           #ExMult
  | l=expr op='/' r=expr       {$Ty = typeOfBinary($l.Ty, $r.Ty, $op);}                           #ExDiv
  | l=expr op='+' r=expr       {$Ty = typeOfPlus($l.Ty, $r.Ty, $op);}                             #ExPlus
  | l=expr op='-' r=expr       {$Ty = typeOfPlus($l.Ty, $r.Ty, $op);}                             #ExMinus
  | '(' expr ')'               {$Ty = $expr.Ty;}                                                  #ExExpr
  ;

stmtsThen returns[WhileBlock *BBThenExit = nullptr;]
  : (statement ';')*
  ;

stmtsElse returns[WhileBlock *BBElseEntry = nullptr;]
  : (statement ';')*
  ;

stmtsWhile
  : (statement ';')*
  ;

statement returns[WhileBlock *BBStmt = nullptr;]
  : var_def[&Functions.back().Locals]                                                           #StmtVar
  | ID op='=' expr                        {typeOfBinary(typeOfVariable($ID), $expr.Ty, $op);}   #StmtAssign
  | ID ('[' i=expr ']')? op='=' r=expr    {typeOfArrayAssign($ID, $i.Ty, $r.Ty, $op);}          #StmtArrayAssign
  | '*' l=expr op='=' r=expr              {typeOfPtrAssign($l.Ty, $r.Ty, $op);}                 #StmtPtrAssign
  | expr                                                                                        #StmtExpr
  | op='if' expr 'then'                   {typeOfInt($expr.Ty, $op);}
    stmtsThen
    ('else' stmtsElse)? 'end'                                                                   #StmtIf
  | op='while' expr 'do'                  {typeOfInt($expr.Ty, $op);}
    stmtsWhile 'end'                                                                            #StmtWhile
  | op='return' expr                      {typeOfReturn($expr.Ty, $op);}                        #StmtReturn
  ;

fun_body
  : (statement ';')*
  ;

parameters
  : '(' param_decl (',' param_decl)* ')'
  ;

fun_def returns[WhileFunctionSymbol *Fun = nullptr;]locals[WhileType Ty = WINT;]
  : 'fun' ({$Ty = WPTR;}'*')? ID
    {Functions.emplace_back($ID.text, $Ty); $Fun = &Functions.back();}
    parameters? 'begin'
    {$Fun->Locals.Size = $Fun->Parameters.Size;}
    fun_body 'end'
  ;

definition
  : var_def[&Globals] ';'   #Var
  | fun_def                 #Fun
  ;
