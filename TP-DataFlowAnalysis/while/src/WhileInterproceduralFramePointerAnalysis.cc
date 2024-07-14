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
// While is distributed isn the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// While. If not, see <https://www.gnu.org/licenses/>.
//
// Contact: florian.brandner@telecom-paris.fr
//

// A simple inter-procedural analysis tracking all possible values that the
// FramePointer might have at any location in the program.

#include "WhileAnalysis.h"
#include "WhileLang.h"
#include "WhileCFG.h"
#include "WhileColor.h"


typedef std::set<unsigned int> WhileFramePointerDomain;

struct WhileFramePointer
  : public WhileInterproceduralDataFlowAnalysis<WhileFramePointerDomain>
{
  std::ostream &dump_entry(std::ostream &s,
                           const WhileFramePointerDomain &value) override
  {
    s << "[";
    bool first = true;
    for(unsigned int fp : value)
    {
      if (!first)
        s << ", ";

      s << fp;
      first = false;
    }
    return s << "]";
  }

  std::ostream &dump_first(std::ostream &s,
                           const WhileFramePointerDomain &value) override
  {
    s << "    ";
    return dump_entry(s, value) << "\n";
  }

  std::ostream &dump_pre(std::ostream &s,
                         const WhileFramePointerDomain &value) override
  {
    return s;
  }

  std::ostream &dump_post(std::ostream &s,
                          const WhileFramePointerDomain &value) override
  {
    return dump_first(s, value);
  }

  virtual WhileFramePointerDomain initialize(const WhileFunction *f) override
  {
    WhileFramePointerDomain result;
    if (f->CallSites.empty())
      result.emplace(f->FrameSize);

    return result;
  }

  // TODO: refactor -- code is reused.
  const WhileFunction *readFunctionOperand(const WhileInstr &i) const
  {
    const WhileProgram *p = i.Block->Function->Program;
    const WhileOperand &op = i.Ops[0];
    switch (op.Kind)
    {
      case WFUNCTION:
        if (op.ValueOrIndex < 0) return nullptr;
        else return p->FunctionsByIndex.at(op.ValueOrIndex) ;

      case WFRAMEPOINTER:
      case WREGISTER:
      case WIMMEDIATE:
      case WBLOCK:
      case WUNKNOWN:
        assert("Operand is not a function.");
    }
    abort();
  }

  WhileFramePointerDomain transfer(const WhileInstr &instr, const WhileFramePointerDomain input) override
  {
    const auto &ops = instr.Ops;
    switch(instr.Opc)
    {
      case WRETURN:
      {
        WhileFramePointerDomain result;
        for(unsigned int value : input)
        {
          unsigned int fs = instr.Block->Function->FrameSize;
          if (fs <= value)
            result.emplace(value - fs);
        }
        return result;
      }
      case WCALL:
      {
        // Ops: Fun Opd = Arg1, Arg2, ... ArgN
        assert(ops.size() > 2);
        const WhileFunction *fun = readFunctionOperand(instr);
        if (fun)
        {
          WhileFramePointerDomain result;
          for(unsigned int value : input)
            result.emplace(value + fun->FrameSize);
          return result;
        }
        else
        {
          // Builtins do not change frame pointer.
          return input;
        }
      }

      case WBRANCHZ:
      case WBRANCH:
      case WSTORE:
      case WLOAD:
      case WPLUS:
      case WMINUS:
      case WMULT:
      case WDIV:
      case WEQUAL:
      case WUNEQUAL:
      case WLESS:
      case WLESSEQUAL:
        // do not change the frame pointer
        return input;
    };
    abort();
  }

  WhileFramePointerDomain join(
                             std::list<WhileFramePointerDomain> inputs) override
  {
    WhileFramePointerDomain result;
    for(const WhileFramePointerDomain &v : inputs)
      result.insert(v.begin(), v.end());

    return result;
  }
};


struct WhileInterproceduralFramePointerAnalysis : public WhileAnalysis
{
  void analyze(const WhileProgram &p) override
  {
    WhileFramePointer WIFPA;
    WIFPA.analyze(p);
    WIFPA.dump(std::cout, p);
  };

  WhileInterproceduralFramePointerAnalysis() : WhileAnalysis("WIFPA",
                                      "Inter-procedural Frame Pointer analysis")
  {
  }
};

WhileInterproceduralFramePointerAnalysis WIFPA;
