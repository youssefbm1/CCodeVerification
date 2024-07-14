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

// The file defines a data structure to represent states of While programs for
// an interpreter. States consist of a memory and a call stack, representing
// symbolic registers of functions, the return address, instruction-, stack-,
// and frame-pointer.

#include "WhileCFG.h"

#pragma once

typedef std::list<WhileInstr>::const_iterator instruction_pointer_t;

struct WhileContext
{
  const WhileFunction *Function;
  const WhileBlock *Block;
  instruction_pointer_t InstructionPointer;
  unsigned int FramePointer;
  std::vector<int> Registers;

  const WhileInstr *LastCall = nullptr;

  WhileContext(const WhileFunction *fun, const WhileBlock *blk,
               instruction_pointer_t ip, unsigned int fp)
    : Function(fun), Block(blk), InstructionPointer(ip), FramePointer(fp)
  {
    Registers.reserve(200);
  }
};

struct WhileState
{
  bool Done = false;
  unsigned int ExitState = -1;
  const WhileProgram *Program;
  std::vector<int> Memory;
  std::list<WhileContext> Context;

  explicit WhileState(const WhileProgram *program, unsigned int stacksize = 1024);

  int readDataOperand(const WhileInstr &i, unsigned int idx) const;
  const WhileFunction *readFunctionOperand(const WhileInstr &i) const;
  const WhileBlock *readBBOperand(const WhileInstr &i, unsigned int idx) const;
  void writeRegisterOperand(const WhileInstr &i, unsigned int idx, int value);

  void step(bool trace = false);
  void run(bool trace = false,
           unsigned int steps = std::numeric_limits<unsigned int>::max());

  std::ostream &dump(std::ostream &s) const;
 };
