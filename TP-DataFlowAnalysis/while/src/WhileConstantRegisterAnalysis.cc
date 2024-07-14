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

// A simple analysis determining whether symbolic registers contain a constant
// value.

#include "WhileAnalysis.h"
#include "WhileLang.h"
#include "WhileCFG.h"
#include "WhileColor.h"


enum WhileConstantKind
{
  TOP,
  BOTTOM,
  CONSTANT
};

struct WhileConstantValue
{
  WhileConstantKind Kind;
  int Value;

  WhileConstantValue() : Kind(TOP), Value(0)
  {
  }

  WhileConstantValue(int value) : Kind(CONSTANT), Value(value)
  {
  }

  WhileConstantValue(WhileConstantKind kind) : Kind(kind), Value(0)
  {
  }
};

bool operator==(const WhileConstantValue &a, const WhileConstantValue &b)
{
  return (a.Kind == b.Kind && a.Value == b.Value);
}

typedef std::map<int, WhileConstantValue> WhileConstantDomain;

std::ostream &operator<<(std::ostream &s, const WhileConstantValue &v)
{
  switch (v.Kind)
  {
    case TOP:
      return s << FLIGHT_GRAY << "⊤" << CRESET;
    case BOTTOM:
      return s << FRED << "⊥" << CRESET;
    case CONSTANT:
      return s << FGREEN << v.Value << CRESET;
  };
  abort();
}

struct WhileConstant : public WhileDataFlowAnalysis<WhileConstantDomain>
{
  std::ostream &dump_first(std::ostream &s,
                           const WhileConstantDomain &value) override
  {
    s << "    [";
    bool first = true;
    for(const auto&[idx, c] : value)
    {
      if (!first)
        s << ", ";

      s << "R" << idx << "=" << c;
      first = false;
    }
    return s << "]\n";
  }

  std::ostream &dump_pre(std::ostream &s,
                         const WhileConstantDomain &value) override
  {
    return s;
  }

  std::ostream &dump_post(std::ostream &s,
                          const WhileConstantDomain &value) override
  {
    return dump_first(s, value);
  }

  static void updateRegisterOperand(const WhileInstr &instr, unsigned int idx,
                             WhileConstantDomain &result,
                             WhileConstantValue value)
  {
    const WhileOperand &op = instr.Ops[idx];
    switch (op.Kind)
    {
      case WREGISTER:
        assert(op.ValueOrIndex >= 0);
        result[op.ValueOrIndex] = value;
        return;

      case WFRAMEPOINTER:
      case WIMMEDIATE:
      case WBLOCK:
      case WFUNCTION:
      case WUNKNOWN:
        assert("Operand is not a register.");
    }
    abort();
  }

  static WhileConstantValue readDataOperand(const WhileInstr &instr,
                                            unsigned int idx,
                                            const WhileConstantDomain &input)
  {
    const WhileOperand &op = instr.Ops[idx];
    switch (op.Kind)
    {
      case WREGISTER:
      {
        assert(op.ValueOrIndex >= 0);
        auto value = input.find(op.ValueOrIndex);
        if (value == input.end())
          return BOTTOM; // register undefined
        else
          return value->second;
      }
      case WIMMEDIATE:
        return op.ValueOrIndex;

      case WFRAMEPOINTER:
          return BOTTOM;

      case WBLOCK:
      case WFUNCTION:
      case WUNKNOWN:
        assert("Operand is not a data value.");
    }
    abort();
  }

  WhileConstantDomain transfer(const WhileInstr &instr, const WhileConstantDomain input) override
  {
    WhileConstantDomain result = input;
    const auto &ops = instr.Ops;
    switch(instr.Opc)
    {
      case WBRANCHZ:
      case WBRANCH:
      case WRETURN:
      case WSTORE:
        // do not write symbolic registers
        break;

      case WCALL:
      {
        // Ops: Fun Opd = Arg1, Arg2, ... ArgN
        assert(ops.size() > 2);
        updateRegisterOperand(instr, 1, result, BOTTOM);
        break;
      }

      case WLOAD:
      {
        // Ops: OpD = [BaseAddress + Offset]
        assert(ops.size() ==  3);
        updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }

      case WPLUS:
      {
        // Ops: OpD = OpA + OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value + b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WMINUS:
      {
        // Ops: OpD = OpA - OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value - b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WMULT:
      {
        // Ops: OpD = OpA * OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value * b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WDIV:
      {
        // Ops: OpD = OpA / OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value / b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WEQUAL:
      {
        // Ops: OpD = OpA == OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value == b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WUNEQUAL:
      {
        // Ops: OpD = OpA != OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value != b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WLESS:
      {
        // Ops: OpD = OpA < OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value < b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
      case WLESSEQUAL:
      {
        // Ops: OpD = OpA <= OpB
        assert(ops.size() ==  3);
        WhileConstantValue a = readDataOperand(instr, 1, input);
        WhileConstantValue b = readDataOperand(instr, 2, input);

        if (a.Kind == CONSTANT && b.Kind == CONSTANT)
          updateRegisterOperand(instr, 0, result, a.Value <= b.Value);
        else
          updateRegisterOperand(instr, 0, result, BOTTOM);
        break;
      }
    };

    return result;
  }

  static WhileConstantValue join(const WhileConstantValue &a,
                                 const WhileConstantValue &b)
  {
    if (a.Kind == TOP)
      return b;
    else if (b.Kind == TOP)
      return a;
    else if (a == b)
      return a;
    else
      return BOTTOM;
  }

  WhileConstantDomain join(std::list<WhileConstantDomain> inputs) override
  {
    WhileConstantDomain result;
    for(WhileConstantDomain r : inputs)
    {
      for(const auto&[idx, value] : r)
      {
        WhileConstantValue &resultvalue = result[idx];
        resultvalue = join(resultvalue, value);
      }
    }

    return result;
  }
};


struct WhileConstantRegisterAnalysis : public WhileAnalysis
{
  void analyze(const WhileProgram &p) override
  {
    WhileConstant WCRA;
    WCRA.analyze(p);
    WCRA.dump(std::cout, p);
  };

  WhileConstantRegisterAnalysis() : WhileAnalysis("WCRA",
                                                  "Constant Register Analysis")
  {
  }
};

WhileConstantRegisterAnalysis WCRA;
