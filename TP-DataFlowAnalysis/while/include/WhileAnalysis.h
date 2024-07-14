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

// This file defines a simple interface to build program analyses for While
// programs.

#include "WhileCFG.h"

#pragma once

// Values of the domain D have to supply:
// - A default constructor (D a; must work)
// - A copy constructor (D a; D b(a); must work)
// - An assignment operator (D a; D b; a = b; must work)
// - A comparison operator (D a; D b; a != b; must work)
//
template<typename D>
struct WhileAnalysisInterface
{
  std::set<const WhileBlock *> WorkList;

  std::map<const WhileBlock*, D> BBOut;

  virtual D transfer(const WhileInstr &i, const D input) = 0;
  virtual D join(std::list<D> inputs) = 0;

  virtual std::ostream &dump_first(std::ostream &s, const D &value) = 0;
  virtual std::ostream &dump_pre(std::ostream &s, const D &value) = 0;
  virtual std::ostream &dump_post(std::ostream &s, const D &value) = 0;

  virtual std::ostream &dump_entry(std::ostream &s, const WhileFunction &f)
  {
    return s << "\n";
  }

  virtual D transf(const WhileInstr &i, const D input)
  {
    return transfer(i, input);
  }

  virtual D join(const WhileBlock *bb)
  {
    std::list<D> bbIn;
    for(const auto &[pred, kind] : bb->Pred)
      bbIn.emplace_back(BBOut[pred]);

    return join(bbIn);
  }

  void iterate()
  {
    while(!WorkList.empty())
    {
      const WhileBlock *bb = *WorkList.begin();
      WorkList.erase(WorkList.begin());

      D bbIn(join(bb));

      for(const WhileInstr &i : bb->Body)
        bbIn = transf(i, bbIn);

      D &bbOut = BBOut[bb];
      if (bbIn != bbOut)
      {
        bbOut = bbIn;
        for(const auto &[kind, succ] : bb->Succ)
          WorkList.emplace(succ);
      }
    }
  }

  std::ostream &dump(std::ostream &s, const WhileProgram &p)
  {
    for(const auto &[name, f] : p.Functions)
    {
      f.dumphead(s);
      dump_entry(s, f);

      for(const WhileBlock &bb : f.Body)
      {
        D bbIn(join(&bb));

        bb.dumphead(s) << "\n";

        dump_first(s, bbIn);
        for (const WhileInstr &i : bb.Body)
        {
          dump_pre(s, bbIn);
          s << std::setw(4) << i.Index << ": ";
          i.dump(s) << "\n";
          bbIn = transf(i, bbIn);
          dump_post(s, bbIn);
        }
      }
    }

    return s;
  }
};

template<typename D>
struct WhileDataFlowAnalysis : public WhileAnalysisInterface<D>
{
  using WhileAnalysisInterface<D>::WorkList;
  using WhileAnalysisInterface<D>::iterate;

  virtual void initialize(const WhileFunction &f)
  {
    WorkList.clear();

    for(const WhileBlock &b : f.Body)
      WorkList.emplace(&b);
  }

  void analyze(const WhileProgram &p)
  {
    for(const auto &[k, f] : p.Functions)
    {
      initialize(f);
      iterate();
    }
  }
};

template<typename D>
struct WhileInterproceduralDataFlowAnalysis : public WhileAnalysisInterface<D>
{
  using WhileAnalysisInterface<D>::WorkList;
  using WhileAnalysisInterface<D>::BBOut;
  using WhileAnalysisInterface<D>::join;
  using WhileAnalysisInterface<D>::transfer;
  using WhileAnalysisInterface<D>::iterate;

  std::map<const WhileInstr*, D> CSOut;

  virtual std::ostream &dump_entry(std::ostream &s, const D &value) = 0;

  virtual std::ostream &dump_entry(std::ostream &s,
                                   const WhileFunction &f) override
  {
    s << "  # [";
    dump_entry(s, initialize(&f));
    for (const WhileInstr *cs : f.CallSites)
    {
      s << ", ";
      dump_entry(s, CSOut[cs]);
    }
    return s << "]\n";
  }

  virtual D initialize(const WhileFunction *f) = 0;

  virtual D join(const WhileBlock *bb)
  {
    std::list<D> bbIn;

    if (bb->isEntry())
    {
      bbIn.emplace_back(initialize(bb->Function));
      for(const WhileInstr *cs : bb->Function->CallSites)
        bbIn.emplace_back(CSOut[cs]);
    }

    for(const auto &[pred, kind] : bb->Pred)
      bbIn.emplace_back(BBOut[pred]);

    return join(bbIn);
  }

  // TODO: refactor, code is duplicated.
  const WhileFunction *readFunctionOperand(const WhileInstr &i) const
  {
    const WhileOperand &op = i.Ops[0];
    switch (op.Kind)
    {
      case WFUNCTION:
        if (op.ValueOrIndex < 0) return nullptr;
        else return i.Block->Function->Program->FunctionsByIndex.at(op.ValueOrIndex) ;

      case WFRAMEPOINTER:
      case WREGISTER:
      case WIMMEDIATE:
      case WBLOCK:
      case WUNKNOWN:
        assert("Operand is not a function.");
    }
    abort();
  }

  virtual void initialize(const WhileProgram &p)
  {
    WorkList.clear();

    const auto main = p.Functions.find("main");
    if (main != p.Functions.end())
      WorkList.emplace(&main->second.Body.front());
    else
    {
      for(const auto &[n, f] : p.Functions)
        WorkList.emplace(&f.Body.front());
    }
  }

  virtual D transf(const WhileInstr &i, const D input) override
  {
    D instrOut = transfer(i, input);

    if (i.Opc == WCALL)
    {
      const WhileFunction *fun = readFunctionOperand(i);

      if (fun)
      {
        D &csOut = CSOut[&i];
        if (csOut != instrOut)
        {
          csOut = instrOut;
          WorkList.emplace(&fun->Body.front());

          // prevent changing BBOut -- WRETURN will update it.
          return BBOut[i.Block];
        }
      }
    }
    else if (i.Opc == WRETURN)
    {
      const auto &callsites = i.Block->Function->CallSites;
      for(const WhileInstr *cs : callsites)
      {
        const WhileBlock *bb = cs->Block;
        D &bbOut = BBOut[bb];
        if (instrOut != bbOut)
        {
          bbOut = instrOut;
          for(const auto &[kind, succ] : bb->Succ)
            WorkList.emplace(succ);
        }
      }
    }

    return instrOut;
  }


  void analyze(const WhileProgram &p)
  {
    initialize(p);
    iterate();
  }
};

struct WhileAnalysis
{
  const char *Description;
  virtual void analyze(const WhileProgram &p) = 0;

  WhileAnalysis(const char *name, const char *descr);
};

extern std::map<std::string, WhileAnalysis*> WhileAnalyses;
