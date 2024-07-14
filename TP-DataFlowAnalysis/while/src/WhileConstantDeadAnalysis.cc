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

// Structure to represent a constant value in the analysis
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

typedef std::map<int, WhileConstantValue> WhileConstantDomain;

// Enumeration to represent the reachability of a block
enum WhileReachability
{
  REACHABLE,
  DEAD
};

// Structure to represent the domain of constant values with reachability information
struct WhileConstantDeadAnalysisDomain : public WhileConstantDomain
{
  WhileConstantDomain abstractDomainMember;
  WhileReachability currentBlockMember = REACHABLE;
  WhileReachability takenBranchMember = DEAD;
};

// Equality operator for WhileConstantValue
extern bool operator==(const WhileConstantValue &a, const WhileConstantValue &b);
// Output stream operator for WhileConstantValue
extern std::ostream &operator<<(std::ostream &s, const WhileConstantValue &v);

// Equality operator for WhileConstantDeadAnalysisDomain
bool operator==(const WhileConstantDeadAnalysisDomain &a, const WhileConstantDeadAnalysisDomain &b)
{
  return (a.abstractDomainMember == b.abstractDomainMember && a.currentBlockMember == b.currentBlockMember && a.takenBranchMember == b.takenBranchMember);
}

// Output stream operator for WhileConstantDeadAnalysisDomain
std::ostream &
operator<<(std::ostream &s, const WhileConstantDeadAnalysisDomain &members)
{
  s << FLIGHT_RED << members << CRESET;
  s << FLIGHT_GREEN << members.currentBlockMember << CRESET;
  s << FLIGHT_BLUE << members.takenBranchMember << CRESET;
  return s;

  abort();
}


struct WhileConstantDead : public WhileDataFlowAnalysis<WhileConstantDeadAnalysisDomain>
{
  // Method to dump the first analysis result
  std::ostream &dump_first(std::ostream &s,
                           const WhileConstantDeadAnalysisDomain &value) override
  {
    s << "    [";
    bool first = true;
    for (const auto &[idx, c] : value.abstractDomainMember)
    {
      if (!first)
        s << ", ";

      s << "R" << idx << "=" << c;
      first = false;
    }

    if (value.currentBlockMember == REACHABLE)
      s << ", Current Block =" << FGREEN << " Reachable";
    else if (value.currentBlockMember == DEAD)
      s << ", Current Block =" << FRED << " Dead";
    s << CRESET;

    if (value.takenBranchMember == REACHABLE)
      s << ", Taken Branch =" << FGREEN << " Reachable";
    else if (value.takenBranchMember == DEAD)
      s << ", Taken Branch = " << FRED << " Dead";

    s << CRESET;
    return s << "]\n";
  }

// Method to dump the pre-analysis result
  std::ostream &dump_pre(std::ostream &s,
                         const WhileConstantDeadAnalysisDomain &value) override
  {
    return s;
  }

  std::ostream &dump_post(std::ostream &s,
                          const WhileConstantDeadAnalysisDomain &value) override
  {
    return dump_first(s, value);
  }

// Method to update the register operand with a new value
  static void updateRegisterOperand(const WhileInstr &instr, unsigned int idx,
                                    WhileConstantDeadAnalysisDomain &result,
                                    WhileConstantValue value)
  {
    const WhileOperand &op = instr.Ops[idx];
    switch (op.Kind)
    {
    case WREGISTER:
      assert(op.ValueOrIndex >= 0);
      result.abstractDomainMember[op.ValueOrIndex] = value;
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

// Method to read the data operand and return its value
  static WhileConstantValue readDataOperand(const WhileInstr &instr,
                                            unsigned int idx,
                                            const WhileConstantDeadAnalysisDomain &input)
  {
    const WhileOperand &op = instr.Ops[idx];
    switch (op.Kind)
    {
    case WREGISTER:
    {
      assert(op.ValueOrIndex >= 0);
      auto value = input.abstractDomainMember.find(op.ValueOrIndex);
      if (value == input.abstractDomainMember.end())
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

  // Method to transfer the analysis state based on the instruction
  WhileConstantDeadAnalysisDomain transfer(const WhileInstr &instr, const WhileConstantDeadAnalysisDomain input) override
  {
    WhileConstantDeadAnalysisDomain result = input;
    const auto &ops = instr.Ops;

    switch (instr.Opc)
    {
    case WBRANCHZ:
    {
      result.currentBlockMember = REACHABLE;
      result.takenBranchMember = REACHABLE;

      WhileConstantValue a = readDataOperand(instr, 0, input);
      if (a.Kind == CONSTANT)
      {
        if (a.Value)
          result.takenBranchMember = DEAD;
        else
          result.currentBlockMember = DEAD;
      }
      break;
    }
    case WBRANCH:
    {
      result.currentBlockMember = DEAD;
      result.takenBranchMember = REACHABLE;
      break;
    }
    case WRETURN:
    {
      result.currentBlockMember = DEAD;
      result.takenBranchMember = DEAD;
      break;
    }
    case WSTORE:
    {
      break;
    }
    case WCALL:
    {
      assert(ops.size() > 2);
      updateRegisterOperand(instr, 1, result, BOTTOM);
      break;
    }

    case WLOAD:
    {
      assert(ops.size() == 3);
      updateRegisterOperand(instr, 0, result, BOTTOM);
      break;
    }

    case WPLUS:
    {
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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
      assert(ops.size() == 3);
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

   WhileConstantDeadAnalysisDomain join(std::list<WhileConstantDeadAnalysisDomain> inputs)
  {
    WhileConstantDeadAnalysisDomain result;

    // we are assuming that everything is reachable (if inputs is empty)
    if (inputs.empty())
    {
      result.currentBlockMember = REACHABLE;
      result.takenBranchMember = REACHABLE;
    }

    for (WhileConstantDeadAnalysisDomain r : inputs)
    {
      if (r.currentBlockMember == REACHABLE)
      {
        for (const auto &[idx, value] : r.abstractDomainMember)
        {
          WhileConstantValue &resultvalue = result.abstractDomainMember[idx];
          resultvalue = join(resultvalue, value);
        }
      }
    }

    return result;
  }
  
  // Method to join the analysis domains for a basic block
  WhileConstantDeadAnalysisDomain join(const WhileBlock *bb)
  {
    std::list<WhileConstantDeadAnalysisDomain> bbIn;

    for (const auto &[pred, kind] : bb->Pred)
      if ((kind == WFALL_THROUGH && BBOut[pred].currentBlockMember == REACHABLE) || (kind == WBRANCH_TAKEN && BBOut[pred].takenBranchMember == REACHABLE))
        bbIn.emplace_back(BBOut[pred]);

    return join(bbIn);
  }
};
// Analysis structure for performing the constant dead analysis
struct WhileConstantDeadAnalysis : public WhileAnalysis
{

  // Analyze the given program
  void analyze(const WhileProgram &p) override
  {
    WhileConstantDead WCDA;
    WCDA.analyze(p);
    WCDA.dump(std::cout, p);
  };

  // Constructor initializing the analysis with name and description
  WhileConstantDeadAnalysis() : WhileAnalysis("WCDA",
                                              "Constant Dead Analysis")
  {
  }
};

// Create an instance of the WhileConstantDeadAnalysis
WhileConstantDeadAnalysis WCDA;