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

// This file defines data structures to represent While programs as control-flow
// graphs, consisting of functions, basic blocks, symbolic registers, and
// 3-address-code-like instructions.

#include "WhileLang.h"

#include <antlr4-runtime.h>

#pragma once

class WhileState;

typedef int (*WhileBuiltinFunction)(WhileState &s, std::vector<int> &ops);

struct WhileBuiltin
{
  int Index;
  std::vector<WhileType> ParameterTypes;
  WhileBuiltinFunction Function;

};

extern std::map<std::string, WhileBuiltin> WhileBuiltins;

enum WhileOpKind
{
  WFRAMEPOINTER,
  WREGISTER,
  WBLOCK,
  WFUNCTION,
  WIMMEDIATE,
  WUNKNOWN
};

const bool WhileOpIsData[] = {true, true, false, false, true, false};

struct WhileOperand
{
  WhileOpKind Kind;
  int ValueOrIndex;
  WhileSymbol *Symbol = nullptr;
  std::string Comment;

  WhileOperand(WhileOpKind kind = WUNKNOWN, int valoridx = 0, const std::string &comment = "")
    : Kind(kind), ValueOrIndex(valoridx), Comment(comment)
  {
  }

  bool isImm() const
  {
    return Kind == WIMMEDIATE;
  }

  bool isZero() const
  {
    return isImm() && ValueOrIndex == 0;
  }

  bool isFunction() const
  {
    return Kind == WFUNCTION;
  }

  bool isBlock() const
  {
    return Kind == WBLOCK;
  }

  bool isData() const
  {
    return WhileOpIsData[Kind];
  }

  std::ostream &dump(std::ostream &s) const;
};

enum WhileOpcode
{
  WCALL,      // Ops: Fun Opd = Arg1, Arg2, ... ArgN
  WLOAD,      // Ops: OpD = [BaseAddress + Offset]
  WSTORE,     // Ops: [BaseAddress + Offset] = ValueToStore
  WPLUS,      // Ops: OpD = OpA + OpB
  WMINUS,     // Ops: OpD = OpA - OpB
  WMULT,      // Ops: OpD = OpA * OpB
  WDIV,       // Ops: OpD = OpA / OpB
  WEQUAL,     // Ops: OpD = OpA == OpB
  WUNEQUAL,   // Ops: OpD = OpA != OpB
  WLESS,      // Ops: OpD = OpA < OpB
  WLESSEQUAL, // Ops: OpD = OpA <= OpB
  WBRANCHZ,   // Ops: Cond, BB
  WBRANCH,    // Ops: BB
  WRETURN     // Ops: VallueToReturn
};

struct WhileBlock;

struct WhileInstr
{
  unsigned int Index;
  unsigned int Line;
  unsigned int OffsetOnLine;

  WhileOpcode Opc;
  std::vector<WhileOperand> Ops;

  WhileBlock *Block;

  WhileInstr(unsigned int idx, unsigned int line, unsigned int offs,
             WhileOpcode opc, WhileBlock *block)
    : Index(idx), Line(line), OffsetOnLine(offs), Opc(opc), Block(block)
  {
  }

  std::ostream &dump(std::ostream &s) const;
};

struct WhileFunction;

enum WhileSuccKind
{
  WFALL_THROUGH,
  WBRANCH_TAKEN
};

struct WhileBlock
{
  unsigned int Index;
  std::list<WhileInstr> Body;
  std::map<WhileSuccKind, WhileBlock *> Succ;
  std::set<std::pair<WhileBlock *, WhileSuccKind> > Pred;
  WhileFunction *Function;

  bool isEntry() const
  {
    return Index == 0;
  }

  WhileBlock(unsigned int idx, WhileFunction *function)
    : Index(idx), Function(function)
  {
  }

  std::ostream &dumpshort(std::ostream &s) const;
  std::ostream &dumphead(std::ostream &s) const;
  std::ostream &dump(std::ostream &s) const;
};

class WhileProgram;

struct WhileFunction
{
  unsigned int Index;
  std::string Name;
  std::list<WhileBlock> Body;
  std::map<std::string, WhileSymbol*> Locals;
  std::map<WhileSymbol*, WhileOperand> Registers;
  unsigned int FrameSize = 0;
  std::list<WhileInstr*> CallSites;
  WhileProgram *Program;

  WhileFunction(std::string name, unsigned int idx, WhileProgram *p)
      : Index(idx), Name(name), Program(p)
  {
  }

  std::ostream &dumpshort(std::ostream &s) const;
  std::ostream &dumphead(std::ostream &s) const;
  std::ostream &dump(std::ostream &s) const;
};

struct WhileProgram
{
  std::map<std::string, WhileFunction> Functions;
  std::vector<WhileFunction*> FunctionsByIndex;
  std::map<std::string, WhileSymbol*> Globals;
  unsigned int DataSize = 0;

  std::ostream &dump(std::ostream &s) const;
};

extern WhileProgram *generateCode(antlr4::tree::ParseTree *tree);
