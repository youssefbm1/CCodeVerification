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

// This is the main file of a simple While interpreter. First command-line
// arguments are processed, then the While input code is parsed, a control-flow
// graph is constructed, and, finally, the interpreter executes the program.

#include <iostream>
#include <string>
#include <cstring>
#include <list>

#include "antlr4-runtime.h"
#include "WhileParser.h"
#include "WhileLexer.h"
#include "WhileBaseListener.h"

#include "WhileLang.h"
#include "WhileCFG.h"
#include "WhileInterpreter.h"

const char *WhileTypes[4] = {"int", "int *", "int[]", "unknown"};

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
  std::cerr << "Usage: " << prog << "[-t] [-d] <input.whl>\n\n"
            << "\t-t\tTrace instructions while interpreting.\n"
            << "\t-d\tDump control-flow graph.\n"
            << "\t-v\tPrint version and license information.\n\n";

  version();
  exit(3);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    usage(argv[0]);

  bool dump = false;
  bool trace = false;
  std::string filename = argv[argc-1];

  for(int i = 1; i < argc-1; i++)
  {
    if (!std::strcmp(argv[i], "-t"))
      trace = true;
    else if (!std::strcmp(argv[i], "-d"))
      dump = true;
    else if (!std::strcmp(argv[i], "-v"))
      version();
    else
      usage(argv[0]);
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

  WhileState s(program);
  s.run(trace);

  return s.ExitState;
}
