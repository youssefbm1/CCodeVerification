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

// This file implements a simple interpreter for While programs, based on
// control-flow graphs. Program states consist of a memoey, a call stack
// capturing symbolic registers of functions, return addresses, the current
// instruction, stack-, and frame-pointer.

#include "WhileInterpreter.h"

#include <cassert>

int WhilePrintInt(WhileState &s, std::vector<int> &ops)
{
  assert(ops.size() == 1);
  std::cout << ops.front() << "\n";
  return 0;
}

int WhilePrintChar(WhileState &s, std::vector<int> &ops)
{
  assert(ops.size() == 1);
  std::cout << (char)ops.front() << "\n";
  return 0;
}

int WhilePrintString(WhileState &s, std::vector<int> &ops)
{
  assert(ops.size() == 1);
  unsigned int ptr = ops.front();
  while(true)
  {
    if (ptr > s.Memory.size())
      return -1;

    char c = s.Memory.at(ptr);
    ptr++;
    if (c)
      std::cout << c;
    else
      return 0;
  }
}

int WhileExit(WhileState &s, std::vector<int> &ops)
{
  assert(ops.size() == 1);
  s.Done = true;
  s.ExitState = ops.front();
  return 0;
}

WhileState::WhileState(const WhileProgram *program, unsigned int stacksize)
  : Program(program), Memory(program->DataSize + stacksize)
{
  const auto main = Program->Functions.find("main");
  if (main != Program->Functions.end())
  {
    const WhileBlock &entryBB = main->second.Body.front();

    Context.emplace_back(&main->second, &entryBB, entryBB.Body.begin(), program->DataSize);

    for(auto [n, g] : Program->Globals)
    {
      unsigned int idx = 0;
      for(int value : g->Init)
      {
        Memory.at(g->Offset + idx++) = value;
      }
    }
  }
}

int WhileState::readDataOperand(const WhileInstr &i, unsigned int idx) const
{
  const WhileOperand &op = i.Ops[idx];
  const WhileContext &ctx = Context.back();
  switch (op.Kind)
  {
    case WFRAMEPOINTER:
      return ctx.FramePointer;
    case WREGISTER:
      return ctx.Registers[op.ValueOrIndex];
    case WIMMEDIATE:
      return op.ValueOrIndex;

    case WBLOCK:
    case WFUNCTION:
    case WUNKNOWN:
      assert("Operand is not a data value.");
  }
  abort();
}

const WhileFunction *WhileState::readFunctionOperand(const WhileInstr &i) const
{
  const WhileOperand &op = i.Ops[0];
  switch (op.Kind)
  {
    case WFUNCTION:
      if (op.ValueOrIndex < 0) return nullptr;
      else return Program->FunctionsByIndex.at(op.ValueOrIndex) ;

    case WFRAMEPOINTER:
    case WREGISTER:
    case WIMMEDIATE:
    case WBLOCK:
    case WUNKNOWN:
      assert("Operand is not a function.");
  }
  abort();
}

const WhileBlock *WhileState::readBBOperand(const WhileInstr &i,
                                            unsigned int idx) const
{
  const WhileContext &ctx = Context.back();
  const WhileOperand &op = i.Ops[idx];
  switch (op.Kind)
  {
    case WBLOCK:
      if (op.ValueOrIndex < 0) return nullptr;
      else
      {
        auto it = ctx.Function->Body.cbegin();
        std::advance(it, op.ValueOrIndex);
        return &*it;
      }

    case WFUNCTION:
    case WFRAMEPOINTER:
    case WREGISTER:
    case WIMMEDIATE:
    case WUNKNOWN:
      assert("Operand is not a function.");
  }
  abort();
}

void WhileState::writeRegisterOperand(const WhileInstr &i, unsigned int idx,
                                      int value)
{
  WhileContext &ctx = Context.back();
  const WhileOperand &op = i.Ops[idx];
  switch (op.Kind)
  {
    case WREGISTER:
      assert(op.ValueOrIndex >= 0);
      if (ctx.Registers.size() <= (unsigned int)op.ValueOrIndex)
        ctx.Registers.resize(op.ValueOrIndex+1);
      ctx.Registers[op.ValueOrIndex] = value;
      return;

    case WIMMEDIATE:
    case WFRAMEPOINTER:
    case WBLOCK:
    case WFUNCTION:
    case WUNKNOWN:
      assert("Operand is not a register.");
  }
  abort();
}

void WhileState::step(bool trace)
{
  if (Context.empty())
  {
    Done = true;
    return;
  }

  WhileContext &ctx = Context.back();

  const WhileBlock *block = ctx.Block;
  const auto &body = block->Body;
  if (ctx.InstructionPointer == body.cend())
  {
    ctx.Block = block->Succ.at(WFALL_THROUGH);
    ctx.InstructionPointer = ctx.Block->Body.cbegin();
  }

  const WhileInstr &instr = *ctx.InstructionPointer;
  const auto &ops = instr.Ops;

  if (trace)
  {
    std::cout << ctx.Function->Name << "(" << ctx.Function->Index << ")::"
              << ctx.Block->Index << "::"
              << ctx.InstructionPointer->Index
              << ": ";
    instr.dump(std::cout);

    std::cout << " FP=" << ctx.FramePointer
              << " SP=" << ctx.FramePointer + ctx.Function->FrameSize;
  }

  ctx.InstructionPointer++;

  switch(instr.Opc)
  {
    case WCALL:
    {
      // Ops: Fun Opd = Arg1, Arg2, ... ArgN
      assert(ops.size() > 2);
      ctx.LastCall = &instr;
      const WhileFunction *fun = readFunctionOperand(instr);

      if (fun)
      {
        const WhileBlock &entryBB = fun->Body.front();
        unsigned int nextFP = ctx.FramePointer + ctx.Function->FrameSize;

        for(unsigned int i = 2; i < ops.size(); i++)
          Memory.at(nextFP + i - 2) = readDataOperand(instr, i);

        Context.emplace_back(fun, &entryBB, entryBB.Body.begin(), nextFP);
      }
      else
      {
        std::vector<int> args;
        for(unsigned int i = 2; i < ops.size(); i++)
          args.emplace_back(readDataOperand(instr, i));

        bool found = false;
        for(const auto[n, b] : WhileBuiltins)
        {
          if (b.Index == ops[0].ValueOrIndex)
          {
            int result = b.Function(*this, args);
            writeRegisterOperand(instr, 1, result);
            found = true;
            break;
          }
        }
        if (!found)
        {
          assert("Unexpected builtin.");
          abort();
        }
      }
      break;
    }
    case WLOAD:
    {
      // Ops: OpD = [BaseAddress + Offset]
      assert(ops.size() ==  3);
      int base = readDataOperand(instr, 1);
      int offset = readDataOperand(instr, 2);

      int result = Memory.at(base + offset);
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WSTORE:
    {
      // Ops: [BaseAddress + Offset] = ValueToStore
      assert(ops.size() ==  3);
      int base = readDataOperand(instr, 0);
      int offset = readDataOperand(instr, 1);
      int value = readDataOperand(instr, 2);

      if (trace)
        std::cout << " writes " << value;

      Memory.at(base + offset) = value;
      break;
    }
    case WPLUS:
    {
      // Ops: OpD = OpA + OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a + b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WMINUS:
    {
      // Ops: OpD = OpA - OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a - b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WMULT:
    {
      // Ops: OpD = OpA * OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a * b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WDIV:
    {
      // Ops: OpD = OpA / OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a / b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WEQUAL:
    {
      // Ops: OpD = OpA == OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a == b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WUNEQUAL:
    {
      // Ops: OpD = OpA != OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a != b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WLESS:
    {
      // Ops: OpD = OpA < OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a < b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WLESSEQUAL:
    {
      // Ops: OpD = OpA <= OpB
      assert(ops.size() ==  3);
      int a = readDataOperand(instr, 1);
      int b = readDataOperand(instr, 2);

      int result = a <= b;
      if (trace)
        std::cout << " writes " << result;

      writeRegisterOperand(instr, 0, result);
      break;
    }
    case WBRANCHZ:
    {
      const WhileBlock *nextBB = readBBOperand(instr, 1);
      if (nextBB)
      {
        if(readDataOperand(instr, 0) == 0)
        {
          if (trace)
            std::cout << " taken";

          ctx.Block = nextBB;
          ctx.InstructionPointer = nextBB->Body.cbegin();
        }
      }
      else
      {
        assert("Invalid branch address.");
        abort();
      }
      break;
    }
    case WBRANCH:
    {
      const WhileBlock *nextBB = readBBOperand(instr, 0);
      if (nextBB)
      {
        ctx.Block = nextBB;
        ctx.InstructionPointer = nextBB->Body.cbegin();
      }
      else
      {
        assert("Invalid branch address.");
        abort();
      }
      break;
    }
    case WRETURN:
    {
      int retval = readDataOperand(instr, 0);

      if (trace)
        std::cout << " returns " << retval;

      Context.pop_back();

      if (Context.empty())
      {
        Done = true;
        ExitState = retval;
      }
      else
      {
        WhileContext &callctx = Context.back();
        assert(callctx.LastCall && "Inconsistent return");
        const WhileInstr *callinstr = callctx.LastCall;
        if(callinstr->Opc == WCALL)
        {
          const WhileOperand &op = callinstr->Ops[1];
          switch (op.Kind)
          {
            case WREGISTER:
              assert(op.ValueOrIndex >= 0);
              if (callctx.Registers.size() <= (unsigned int)op.ValueOrIndex)
                callctx.Registers.resize(op.ValueOrIndex+1);
              callctx.Registers[op.ValueOrIndex] = retval;
              break;

            case WIMMEDIATE:
            case WFRAMEPOINTER:
            case WBLOCK:
            case WFUNCTION:
            case WUNKNOWN:
              assert("Operand is not a register.");
              abort();
          }
        }
        else
        {
          assert("Returning to instruction that is not a WCALL.");
          abort();
        }
      }
      break;
    }
  }

  if (trace)
    std::cout << "\n";
}

void WhileState::run(bool trace, unsigned int steps)
{
  while(steps != 0 && !Done)
  {
    step(trace);
    steps--;
  }
}

std::ostream &WhileState::dump(std::ostream &s) const
{
  unsigned int ident = 0;
  for(const WhileContext &ctx : Context)
  {
    const auto IP = ctx.InstructionPointer;
    s << std::setw(2*ident++) << "|"
      << ctx.Function->Name << "(" << ctx.Function->Index << ")::"
      << ctx.Block->Index << "::" ;

    if (IP != ctx.Block->Body.end())
      s << IP->Index << "\t # " << IP->Line << ":" << IP->OffsetOnLine << "\n";
    else
      s << "??\n";
  }

  unsigned int idx = 0;
  for(int regval : Context.back().Registers)
  {
    s << std::setw(2*ident++) << "|"
      << "R" << std::left << std::setw(2) << idx++ << std::right << ": "
      << regval << "\n";
  }

  return s;
}
