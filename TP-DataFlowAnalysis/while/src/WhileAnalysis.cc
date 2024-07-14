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

// This is the main file of a simple While analyzer. First command-line
// arguments are processed, then the While input code is parsed, a control-flow
// graph is constructed, and, finally, the program is analyzed.

#include "WhileAnalysis.h"
#include "WhileLang.h"
#include "WhileCFG.h"
#include "WhileColor.h"

#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <numeric>

#include "antlr4-runtime.h"
#include "WhileParser.h"
#include "WhileLexer.h"
#include "WhileBaseListener.h"


const char *WhileTypes[4] = {"int", "int *", "int[]", "unknown"};

std::map<std::string, WhileAnalysis*> WhileAnalyses;

WhileAnalysis::WhileAnalysis(const char *name, const char *descr)
  : Description(descr)
{
  WhileAnalyses.emplace(name, this);
}

static void version()
{
  std::cout << "While  Copyright  2023  Florian Brandner\n"
               "This program comes with ABSOLUTELY NO WARRANTY.\n"
               "This is free software, and you are welcome to redistribute it "
               "under certain conditions. See the license file in the source "
               "distribution for more details.\n";
}

static void usage(const char *prog)
{
  std::cerr << "Usage: " << prog << "[-d] <input.whl>\n\n"
            << "\t-d\tDump control-flow graph.\n"
            << "\t-l\tPrint list of available analyses.\n"
            << "\t-v\tPrint version and license information.\n\n";

  version();
  exit(3);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    usage(argv[0]);

  bool dump = false;
  std::string filename = argv[argc-1];
  std::set<WhileAnalysis*> ToRun;

  for(int i = 1; i < argc-1; i++)
  {
    if (!std::strcmp(argv[i], "-d"))
      dump = true;
    else if (!std::strcmp(argv[i], "-l"))
    {
      std::cout << "List of available analyses:\n";
      for(const auto&[name, a] : WhileAnalyses)
        std::cout << "  " << std::left << std::setw(10) << name << std::right
                  << a->Description << "\n";

      return 0;
    }
    else if (!std::strcmp(argv[i], "-v"))
      version();
    else
    {
      auto a = WhileAnalyses.find(argv[i]);
      if (a == WhileAnalyses.end())
      {
        std::cerr << "Analysis '" << argv[i]
                  << "' unknown. Use '-l' to display list of analyses.\n\n";
        return 1;
      }
      else
        ToRun.emplace(a->second);
    }
  }

  antlr4::ANTLRFileStream input(filename);
  WhileLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  WhileParser parser(&tokens);

  antlr4::tree::ParseTree *tree = parser.program();

  if (parser.getNumberOfSyntaxErrors() != 0)
    return 1;

  if (parser.Error)
    return 2;

  WhileProgram *program = generateCode(tree);

  if (dump)
    program->dump(std::cout);

  for(WhileAnalysis *a : ToRun)
    a->analyze(*program);

  return 0;
}
