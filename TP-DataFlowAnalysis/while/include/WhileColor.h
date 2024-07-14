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

// A list of color codes in order to modify the foreground/background color on
// Linux terminals using ASCII escape codes.

#pragma once

enum ColorCodes
{
  CRESET = 0,
  CBOLD = 1,

  FBLACK = 30,
  FRED,
  FGREEN,
  FORANGE,
  FBLUE,
  FPURPLE,
  FCYAN,
  FLIGHT_GRAY,

  FDARK_GRAY = 90,
  FLIGHT_RED,
  FLIGHT_GREEN,
  FYELLOW,
  FLIGHT_BLUE,
  FLIGHT_PURPLE,
  FLIGHT_CYAN,
  FWHITE,

  BBLACK = 40,
  BRED,
  BGREEN,
  BORANGE,
  BBLUE,
  BPURPLE,
  BCYAN,
  BLIGHT_GRAY,

  BDARK_GRAY = 100,
  BLIGHT_RED,
  BLIGHT_GREEN,
  BYELLOW,
  BLIGHT_BLUE,
  BLIGHT_PURPLE,
  BLIGHT_CYAN,
  BWHITE
};

inline std::ostream &operator<<(std::ostream& s, ColorCodes c) {
  return s << "\033[" << (int)c << "m";
}
