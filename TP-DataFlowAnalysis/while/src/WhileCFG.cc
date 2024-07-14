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

// This file implements a simple code generator that produces a control-flow
// graph for each function and represents the code using symbolic registers and
// simple 3-address-code-like instructions.

#include "WhileCFG.h"

#include "WhileBaseListener.h"

#include <cassert>

// implemented in WhileInterpreter.cc
extern int WhilePrintInt(WhileState &s, std::vector<int> &ops);
extern int WhilePrintChar(WhileState &s, std::vector<int> &ops);
extern int WhilePrintString(WhileState &s, std::vector<int> &ops);
extern int WhileExit(WhileState &s, std::vector<int> &ops);

std::map<std::string, WhileBuiltin> WhileBuiltins =
{
  {"printint"   , {-1, {WINT}, &WhilePrintInt}},
  {"printchar"  , {-2, {WINT}, &WhilePrintChar}},
  {"printptr",    {-3, {WPTR}, &WhilePrintInt}},
  {"printstring", {-4, {WPTR}, &WhilePrintString}},
  {"exit"       , {-5, {WINT}, &WhileExit}}
};

const char *WhileOpcodes[] = {"WCALL", "WLOAD", "WSTORE", "WPLUS", "WMINUS",
                              "WMULT", "WDIR", "WEQUAL", "WUNEQUAL", "WLESS",
                              "WLESSEQUAL", "WBRANCHZ", "WBRANCH", "WRETURN"};

const char *WhileSuccKinds[] = {"FT", "BT"};

class  WhileCodeGenListener : public WhileBaseListener {
public:
  WhileProgram *Program;
  WhileFunction *CurrentFunction = nullptr;
  WhileBlock *CurrentBlock = nullptr;

  unsigned int FreeRegister;
  WhileOperand FramePointer;

  WhileCodeGenListener()
    : Program(new WhileProgram()), FreeRegister(0),
      FramePointer(WFRAMEPOINTER)
  {
  }

  bool useRegister(WhileSymbol *sym)
  {
    return !sym->AddressTaken && sym->Size == 1;
  }

  std::pair<bool, WhileOperand> registerOfVar(std::string name)
  {
    auto local = CurrentFunction->Locals.find(name);
    if (local != CurrentFunction->Locals.end() && useRegister(local->second))
    {
      auto reg = CurrentFunction->Registers.find(local->second);
      if(reg != CurrentFunction->Registers.end())
      {
        return std::pair(true, reg->second);
      }
    }

    return std::pair(false, WhileOperand());;
  }

  WhileOperand getFunOp(const std::string &name)
  {
    auto f = Program->Functions.find(name);
    if (f != Program->Functions.end())
      return WhileOperand(WFUNCTION, f->second.Index, name);
    else
    {
      auto b = WhileBuiltins.find(name);
      assert(b != WhileBuiltins.end());
      return WhileOperand(WFUNCTION, b->second.Index, b->first);
    }
    abort();
  }

  WhileOperand getBBOp(const WhileBlock *bb)
  {
    return WhileOperand(WBLOCK, bb->Index);
  }

  WhileOperand getValOp(int value)
  {
    return WhileOperand(WIMMEDIATE, value);
  }

  WhileOperand getRegOp()
  {
    return WhileOperand(WREGISTER, FreeRegister++);
  }

  WhileBlock *newBlock(bool fallthrough)
  {
    WhileBlock *pred = CurrentBlock;

    CurrentFunction->Body.emplace_back(CurrentFunction->Body.size(),
                                       CurrentFunction);
    CurrentBlock = &CurrentFunction->Body.back();

    if (fallthrough)
    {
      pred->Succ.emplace(WFALL_THROUGH, CurrentBlock);
      CurrentBlock->Pred.emplace(pred, WFALL_THROUGH);
    }

    return pred;
  }

  void newEdge(WhileBlock *pred, WhileBlock *succ)
  {
    bool inserted = pred->Succ.emplace(WBRANCH_TAKEN, succ).second;
    succ->Pred.emplace(pred, WBRANCH_TAKEN);

    assert(inserted && "Multiple taken branches");
  }


  WhileInstr &emitInstr(antlr4::Token *t, WhileOpcode opc,
                        WhileBlock *block = nullptr)
  {
    if (block == nullptr)
      block = CurrentBlock;

    block->Body.emplace_back(block->Body.size(),
                             t->getLine(), t->getCharPositionInLine(),
                             opc, block);
    return block->Body.back();
  }

  WhileInstr &emitStore(antlr4::Token *t, WhileOperand address,
                        WhileOperand offset, WhileOperand valuetostore)
  {
    WhileInstr &store = emitInstr(t, WSTORE);
    store.Ops.emplace_back(address);
    store.Ops.emplace_back(offset);
    store.Ops.emplace_back(valuetostore);

    return store;
  }

  WhileInstr &emitLoad(antlr4::Token *t, WhileOperand dest,
                       WhileOperand address, WhileOperand offset)
  {
    WhileInstr &load = emitInstr(t, WLOAD);
    load.Ops.emplace_back(dest);
    load.Ops.emplace_back(address);
    load.Ops.emplace_back(offset);

    return load;
  }

  WhileInstr &emitBinary(antlr4::Token *t, WhileOpcode opc, WhileOperand dest,
                         WhileOperand a, WhileOperand b)
  {
    WhileInstr &binary = emitInstr(t, opc);
    binary.Ops.emplace_back(dest);
    binary.Ops.emplace_back(a);
    binary.Ops.emplace_back(b);

    return binary;
  }

  WhileInstr &emitPlus(antlr4::Token *t, WhileOperand dest, WhileOperand a,
                       WhileOperand b)
  {
    return emitBinary(t, WPLUS, dest, a, b);
  }

  void emitBranch(antlr4::Token *t, WhileBlock *block, WhileBlock *dest)
  {
    WhileOpcode lastopc = block->Body.empty() ? WPLUS : block->Body.back().Opc;
    switch (lastopc)
    {
      case WRETURN:
      case WBRANCH:
        // no branch needed
        return;

      case WBRANCHZ:
        newBlock(true);
        // fall-through
      case WCALL:
      case WLOAD:
      case WSTORE:
      case WPLUS:
      case WMINUS:
      case WMULT:
      case WDIV:
      case WEQUAL:
      case WUNEQUAL:
      case WLESS:
      case WLESSEQUAL:
      {
        WhileInstr &branch = emitInstr(t, WBRANCH, block);
        branch.Ops.emplace_back(getBBOp(dest));
        newEdge(block, dest);
        return;
      }
    };
    abort();
  }


  std::pair<WhileOperand, WhileOperand> getVarAddress(std::string name)
  {
    auto local = CurrentFunction->Locals.find(name);
    auto global = Program->Globals.find(name);

    WhileOperand base = getValOp(0);
    WhileOperand offset = getValOp(0);
    if (local != CurrentFunction->Locals.end())
    {
      assert(CurrentFunction->Registers.find(local->second) == CurrentFunction->Registers.end());
      base = FramePointer;
      offset = getValOp(local->second->Offset);
      if (local->second->Offset)
        offset.Symbol = local->second;
      else
        base.Symbol = local->second;
    }
    else
    {
      assert(global != Program->Globals.end());
      offset = getValOp(global->second->Offset);
      offset.Symbol = global->second;
    }

    return std::pair(base, offset);
  }

  std::pair<WhileOperand, WhileOperand> computeArrayAddr(std::string name,
      WhileOperand arrayIndex, antlr4::Token *token)
  {
    auto [base, offset] = getVarAddress(name);
    WhileOperand arrayBase;

    if (arrayBase.isZero())
      arrayBase = offset;
    else
    {
      if (offset.isZero())
        arrayBase = base;
      else
        emitPlus(token, arrayBase = getRegOp(), base, offset);
    }

    return std::pair(arrayBase, arrayIndex);
  }

  virtual void enterFun_def(WhileParser::Fun_defContext *ctx) override
  {
    FreeRegister = 0;
    auto [f, b] = Program->Functions.try_emplace(ctx->ID()->getText(),
        ctx->ID()->getText(), Program->Functions.size(), Program);
    CurrentFunction = &f->second;
    Program->FunctionsByIndex.emplace_back(CurrentFunction);

    newBlock(false);

    for(WhileSymbol &p : ctx->Fun->Parameters.Symbols)
    {
      CurrentFunction->Locals.emplace(p.Name, &p);
      CurrentFunction->FrameSize += p.Size;

      if (useRegister(&p))
      {
        WhileOperand reg(getRegOp());
        reg.Symbol = &p;
        CurrentFunction->Registers.emplace(&p, reg);
        emitLoad(ctx->getStart(), reg, FramePointer, getValOp(p.Offset));
      }
    }
  }

  virtual void enterVar(WhileParser::VarContext *ctx) override
  {
    WhileSymbol *sym = ctx->var_def()->Sym;

    Program->Globals.emplace(sym->Name, sym);
    Program->DataSize += sym->Size;
  }

  virtual void exitStmtVar(WhileParser::StmtVarContext *ctx) override
  {
    WhileSymbol *sym = ctx->var_def()->Sym;
    antlr4::Token *token = ctx->getStart();

    CurrentFunction->Locals.emplace(sym->Name, sym);
    CurrentFunction->FrameSize += sym->Size;

    bool usereg = useRegister(sym);
    WhileOperand reg;
    if(usereg)
    {
      reg = getRegOp();
      reg.Symbol = sym;
      CurrentFunction->Registers.emplace(sym, reg);
    }

    unsigned int idx = 0;
    for(int value : sym->Init)
    {
      if(usereg)
      {
        emitPlus(token, reg, getValOp(0), getValOp(value));
      }
      else
      {
        WhileOperand var(getValOp(sym->Offset + idx));
        var.Symbol = sym;

        emitStore(token, FramePointer, var, getValOp(value));
      }
    }
  }

  virtual void exitStmtAssign(WhileParser::StmtAssignContext *ctx) override
  {
    std::string name = ctx->ID()->getText();
    const WhileOperand &valuetostore = ctx->expr()->Op;
    antlr4::Token *token = ctx->getStart();
    auto [usereg, regop] = registerOfVar(name);
    if (usereg)
      emitPlus(token, regop, getValOp(0), valuetostore);
    else
    {
      auto [base, offset] = getVarAddress(name);
      emitStore(token, base, offset, valuetostore);
    }
  }

  virtual void exitStmtArrayAssign(WhileParser::StmtArrayAssignContext *ctx) override
  {
    auto [base, index] = computeArrayAddr(ctx->ID()->getText(), ctx->i->Op,
                                          ctx->getStart());
    emitStore(ctx->getStart(), base, index, ctx->r->Op);
  }

  virtual void exitStmtPtrAssign(WhileParser::StmtPtrAssignContext *ctx) override
  {
    emitStore(ctx->getStart(), ctx->l->Op, getValOp(0), ctx->r->Op);
  }

  virtual void enterStmtIf(WhileParser::StmtIfContext *ctx) override
  {
    ctx->BBStmt = CurrentBlock;
  }

  virtual void enterStmtsThen(WhileParser::StmtsThenContext *ctx) override
  {
    newBlock(true);
  }

  virtual void exitStmtsThen(WhileParser::StmtsThenContext *ctx) override
  {
    ctx->BBThenExit = CurrentBlock;
  }

  virtual void enterStmtsElse(WhileParser::StmtsElseContext *ctx) override
  {
    newBlock(false);
    ctx->BBElseEntry = CurrentBlock;
  }

  virtual void exitStmtIf(WhileParser::StmtIfContext *ctx) override
  {
    if (!CurrentBlock->Body.empty())
      newBlock(true);

    antlr4::Token *t = ctx->getStart();
    WhileBlock *bbStmt = ctx->BBStmt;
    WhileBlock *bbEnd = CurrentBlock;
    WhileBlock *bbThenExit = ctx->stmtsThen()->BBThenExit;
    WhileBlock *bbElseEntry = ctx->stmtsElse() ? ctx->stmtsElse()->BBElseEntry : bbEnd;

    WhileInstr &condBranch = emitInstr(t, WBRANCHZ, bbStmt);
    condBranch.Ops.emplace_back(ctx->expr()->Op);
    condBranch.Ops.emplace_back(getBBOp(bbElseEntry));
    newEdge(bbStmt, bbElseEntry);
    // fall-through added by enterStmtsThen

    if (ctx->stmtsElse())
      emitBranch(t, bbThenExit, bbEnd);
  }

  virtual void enterStmtWhile(WhileParser::StmtWhileContext *ctx) override
  {
    if (!CurrentBlock->Body.empty())
      newBlock(true);

    ctx->BBStmt = CurrentBlock;
  }

  virtual void enterStmtsWhile(WhileParser::StmtsWhileContext *ctx) override
  {
    newBlock(true);
  }

  virtual void exitStmtWhile(WhileParser::StmtWhileContext *ctx) override
  {
    antlr4::Token *t = ctx->getStart();
    WhileBlock *bbStmt = ctx->BBStmt;
    emitBranch(t, CurrentBlock, bbStmt);
    newBlock(false);

    WhileInstr &condBranch = emitInstr(t, WBRANCHZ, bbStmt);
    condBranch.Ops.emplace_back(ctx->expr()->Op);
    condBranch.Ops.emplace_back(getBBOp(CurrentBlock));
    newEdge(bbStmt, CurrentBlock);
    // fall-through of bbStmt added in enterStmtsWhile
  }

  virtual void exitStmtReturn(WhileParser::StmtReturnContext *ctx) override
  {
    antlr4::Token *t = ctx->getStart();
    WhileInstr &ret = emitInstr(t, WRETURN);
    ret.Ops.emplace_back(ctx->expr()->Op);
  }

  virtual void exitExN(WhileParser::ExNContext *ctx) override
  {
    ctx->Op = getValOp(std::stoi(ctx->N()->getText()));
  }

  virtual void exitExID(WhileParser::ExIDContext *ctx) override
  {
    std::string name = ctx->ID()->getText();
    auto [usereg, regop] = registerOfVar(name);
    if (usereg)
      ctx->Op = regop;
    else
    {
      auto [base, offset] = getVarAddress(name);
      emitLoad(ctx->getStart(), ctx->Op = getRegOp(), base, offset);
    }
  }

  virtual void exitExCall(WhileParser::ExCallContext *ctx) override
  {
    antlr4::Token *t = ctx->getStart();
    WhileInstr &call = emitInstr(t, WCALL);
    WhileOperand funop(getFunOp(ctx->ID()->getText()));
    call.Ops.emplace_back(funop);
    call.Ops.emplace_back(ctx->Op = getRegOp());

    for(const WhileParser::ExprContext*ex : ctx->call_args()->expr())
      call.Ops.emplace_back(ex->Op);

    if (0 <= funop.ValueOrIndex)
    {
      Program->FunctionsByIndex.at(funop.ValueOrIndex)
        ->CallSites.emplace_back(&call);
    }

    newBlock(true);
  }

  virtual void exitExPtr(WhileParser::ExPtrContext *ctx) override
  {
    emitLoad(ctx->getStart(), ctx->Op = getRegOp(), ctx->expr()->Op, getValOp(0));
  }

  virtual void exitExAddr(WhileParser::ExAddrContext *ctx) override
  {
    auto [base, offset] = getVarAddress(ctx->ID()->getText());
    if (base.isZero())
      ctx->Op = offset;
    else
    {
      if (offset.isZero())
        ctx->Op = base;
      else
        emitPlus(ctx->getStart(), ctx->Op = getRegOp(), base, offset);
    }
  }

  virtual void exitExArrayAddr(WhileParser::ExArrayAddrContext *ctx) override
  {
    auto [base, index] = computeArrayAddr(ctx->ID()->getText(), ctx->expr()->Op,
                                          ctx->getStart());

    if (index.isZero())
      ctx->Op = base;
    else if (base.isZero())
    {
      if (!index.Symbol)
        index.Symbol = base.Symbol;
      ctx->Op = index;
    }
    else if (base.isImm() && !index.isImm())
    {
      base.ValueOrIndex += index.ValueOrIndex;
      ctx->Op = base;
    }
    else
      emitPlus(ctx->getStart(), ctx->Op = getRegOp(), base, index);
  }

  virtual void exitExPlus(WhileParser::ExPlusContext *ctx) override
  {
    emitPlus(ctx->getStart(), ctx->Op = getRegOp(), ctx->l->Op, ctx->r->Op);
  }

  virtual void exitExMinus(WhileParser::ExMinusContext *ctx) override
  {
    emitBinary(ctx->getStart(), WMINUS, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExMult(WhileParser::ExMultContext *ctx) override
  {
    emitBinary(ctx->getStart(), WMULT, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExDiv(WhileParser::ExDivContext *ctx) override
  {
    emitBinary(ctx->getStart(), WDIV, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExEqual(WhileParser::ExEqualContext *ctx) override
  {
    emitBinary(ctx->getStart(), WEQUAL, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExUnequal(WhileParser::ExUnequalContext *ctx) override
  {
    emitBinary(ctx->getStart(), WUNEQUAL, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExLess(WhileParser::ExLessContext *ctx) override
  {
    emitBinary(ctx->getStart(), WLESS, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExLessEqual(WhileParser::ExLessEqualContext *ctx) override
  {
    emitBinary(ctx->getStart(), WLESSEQUAL, ctx->Op = getRegOp(), ctx->l->Op,
               ctx->r->Op);
  }

  virtual void exitExArray(WhileParser::ExArrayContext *ctx) override
  {
    auto [base, index] = computeArrayAddr(ctx->ID()->getText(), ctx->expr()->Op,
                                          ctx->getStart());
    emitLoad(ctx->getStart(), ctx->Op = getRegOp(), base, index);
  }

  virtual void exitExExpr(WhileParser::ExExprContext *ctx) override
  {
    ctx->Op = ctx->expr()->Op;
  }

  virtual void exitFun_def(WhileParser::Fun_defContext *ctx) override
  {
    WhileOpcode lastopc = CurrentBlock->Body.empty() ? WPLUS :
                                                  CurrentBlock->Body.back().Opc;
    switch (lastopc)
    {
      case WRETURN:
      case WBRANCH:
        break;

      case WBRANCHZ:
        newBlock(true);
        // fall-through
      case WCALL:
      case WLOAD:
      case WSTORE:
      case WPLUS:
      case WMINUS:
      case WMULT:
      case WDIV:
      case WEQUAL:
      case WUNEQUAL:
      case WLESS:
      case WLESSEQUAL:
      {
        antlr4::Token *t = ctx->getStop();
        WhileInstr &ret = emitInstr(t, WRETURN);
        ret.Ops.emplace_back(getValOp(0));
      }
    }
  }
};

std::ostream &WhileOperand::dump(std::ostream &s) const
{
  switch (Kind)
  {
    case WUNKNOWN:      return s << "UKN";
    case WFRAMEPOINTER: return s << "FP ";
    case WBLOCK:        return s << "BB" << std::left <<std::setw(2)
                                 << ValueOrIndex << std::right;
    case WFUNCTION:     return s << "F" << std::left <<std::setw(3)
                                 << ValueOrIndex << std::right;
    case WREGISTER:     return s << "R" << std::left <<std::setw(2)
                                 << ValueOrIndex << std::right;
    case WIMMEDIATE:    return s << std::left << std::setw(3) << ValueOrIndex
                                << std::right;
  }
  abort();
}

std::ostream &WhileInstr::dump(std::ostream &s) const
{
  s << std::setw(10) << WhileOpcodes[Opc] << "  ";
  bool first = true;
  std::stringstream tmp;
  for (const WhileOperand &op : Ops)
  {
    if (!first)
      tmp << ", ";
    op.dump(tmp);
    first = false;
  }
  s << std::left << std::setw(20) << tmp.str() << std::right << " # " << Line << ":" << OffsetOnLine;

  first = true;
  for (const WhileOperand &op : Ops)
  {
    if (op.Symbol)
    {
      if (first)
        s << ":";
      s << " " << op.Symbol->Name;
      first = false;
    }
    if (!op.Comment.empty())
    {
      if (first)
        s << ":";
      s << " " << op.Comment;
      first = false;
    }
  }

  return s;
}

std::ostream &WhileBlock::dumpshort(std::ostream &s) const
{
  return s << "BB" << Index;
}

std::ostream &WhileBlock::dumphead(std::ostream &s) const
{
  dumpshort(s) << ": [";
  bool first = true;
  for(const auto &[pred, kind] : Pred)
  {
    if (!first)
      s << ", ";
    s << "BB" << pred->Index << " (" << WhileSuccKinds[kind] << ")";
    first = false;
  }
  s << "] -> [";
  first = true;
  for(auto &[kind, succ] : Succ)
  {
    if (!first)
      s << ", ";
    s << "BB" << succ->Index << " (" << WhileSuccKinds[kind] << ")";
    first = false;
  }
  return s << "]";
}

std::ostream &WhileBlock::dump(std::ostream &s) const
{
  dumphead(s) << "\n";

  for (const WhileInstr &i : Body)
  {
    s << std::setw(4) << i.Index << ": ";
    i.dump(s) << "\n";
  }

  return s;
}

std::ostream &WhileFunction::dumpshort(std::ostream &s) const
{
  return s << "fun " << Index << ": " << Name;
}

std::ostream &WhileFunction::dumphead(std::ostream &s) const
{
  dumpshort(s);
  s << ": [";
  bool first = true;
  for(const WhileInstr *cs : CallSites)
  {
    WhileBlock *block = cs->Block;
    if (!first)
      s << ", ";
    s << block->Function->Name << "::BB" << block->Index << "::" << cs->Index;
    first = false;
  }
  s << "]\n  # " << FrameSize << "\n";
  for (const auto& [name, sym] : Locals)
  {
    s << "  # " << name << ": FP + " << sym->Offset;
    auto reg = Registers.find(sym);
    if (reg != Registers.end())
    {
      s << " ";
      reg->second.dump(s);
    }

    s << " {";
    first = true;
    for(int value : sym->Init)
    {
      if (!first)
        s << ", ";
      s << value;
      first = false;
    }
    s << "}\n";
  }

  return s;
}

std::ostream &WhileFunction::dump(std::ostream &s) const
{
  dumphead(s);
  for (const WhileBlock &b : Body)
    b.dump(s);

  return s;
}

std::ostream &WhileProgram::dump(std::ostream &s) const
{
  s << "# " << DataSize << "\n";
  for (const auto& [name, sym] : Globals)
  {
    s << "# " << name << ": " << sym->Offset << " {";
    bool first = true;
    for(int value : sym->Init)
    {
      if (!first)
        s << ", ";
      s << value;
      first = false;
    }
    s << "}\n";
  }

  for (const auto& [k, f] : Functions)
    f.dump(s);

  return s;
}


WhileProgram *generateCode(antlr4::tree::ParseTree *tree)
{
  WhileCodeGenListener WCGL;
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&WCGL, tree);

  return WCGL.Program;
}
