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

// This file implements a simple dead code analysis, i.e., marks code that can
// never be executed.

#include "WhileAnalysis.h"
#include "WhileLang.h"
#include "WhileCFG.h"
#include "WhileColor.h"

enum WhileReachability
{
  REACHABLE,
  DEAD
};

std::ostream &operator<<(std::ostream &s, WhileReachability r)
{
  switch (r)
  {
    case DEAD:
      return s << FRED << "DEAD" << CRESET;
    case REACHABLE:
      return s << FGREEN << "REACHABLE" << CRESET;
  };
  abort();
}

struct WhileDeadCode : public WhileDataFlowAnalysis<WhileReachability>
{
  std::ostream &dump_first(std::ostream &s,
                           const WhileReachability &value) override
  {
    return s;
  }

  std::ostream &dump_pre(std::ostream &s,
                         const WhileReachability &value) override
  {
    switch (value)
    {
      case DEAD:
        return s << FRED;
      case REACHABLE:
        return s << FGREEN;
    };
    abort();
  }

  std::ostream &dump_post(std::ostream &s,
                          const WhileReachability &value) override
  {
    return s << CRESET;
  }

  WhileReachability transfer(const WhileInstr &i, const WhileReachability input) override
  {
    WhileReachability result = input;
    switch(i.Opc)
    {
      case WBRANCH:
      case WRETURN:
        // code after those instructions is definitely dead
        result = DEAD;
        break;

      case WCALL:
        // TODO: code after a call might be dead
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
      case WBRANCHZ:
        // do not render code dead
        break;
    };

    return result;
  }

  WhileReachability join(std::list<WhileReachability> inputs) override
  {
    if (inputs.empty())
      return REACHABLE;

    for(WhileReachability r : inputs)
    {
      if (r == REACHABLE)
        return REACHABLE;
    }

    return DEAD;
  }
};


struct WhileDeadCodeAnalysis : public WhileAnalysis
{
  void analyze(const WhileProgram &p) override
  {
    WhileDeadCode WDCA;
    WDCA.analyze(p);
    WDCA.dump(std::cout, p);
  };

  WhileDeadCodeAnalysis() : WhileAnalysis("WDCA", "Dead Code Analysis")
  {
  }
};

WhileDeadCodeAnalysis WDCA;
