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

// This file defines data structures to track variable/function symbols of While
// programs, which are used during semantic/type checking.

#include <string>
#include <list>

#pragma once

enum WhileType
{
  WINT,
  WPTR,
  WARY,
  WERR
};

extern const char *WhileTypes[4];

struct WhileSymbol
{
  std::string Name;
  WhileType Type;
  unsigned int Size;
  unsigned int Offset;
  bool AddressTaken = false;
  std::list<int> Init;

  WhileSymbol(const std::string &name, WhileType type, unsigned int size,
              unsigned int offset)
    : Name(name), Type(type), Size(size), Offset(offset)
  {
  }
};

struct WhileScope
{
  std::list<WhileSymbol> Symbols;
  unsigned int Size = 0;
};

struct WhileFunctionSymbol
{
  std::string Name;
  WhileType Type;
  WhileScope Locals;
  WhileScope Parameters;

  explicit WhileFunctionSymbol(const std::string &name, WhileType type)
    : Name(name), Type(type)
  {
  }
};
