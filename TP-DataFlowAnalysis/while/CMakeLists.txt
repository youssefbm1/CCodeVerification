# This file is part of While, an educational programming language and program
# analysis framework.
#
#   Copyright 2023 Florian Brandner
#
# While is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# While is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# While. If not, see <https://www.gnu.org/licenses/>.
#
# Contact: florian.brandner@telecom-paris.fr
#

cmake_minimum_required(VERSION 3.10)
project(while)

set(CMAKE_CXX_STANDARD 17)

set(ANTLR4_TOOL         /cal/homes/brandner/opt/antlr4/antlr4)
set(ANTLR4_INCLUDE_DIR  /cal/homes/brandner/opt/antlr4/include/antlr4-runtime/)
set(ANTLR4_LIB_DIR      /cal/homes/brandner/opt/antlr4/lib/)
set(ANTLR4LIBRARY       antlr4-runtime)

add_compile_options(-Wno-attributes -Wno-unused-variable -Wall -g)
include_directories(${ANTLR4_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
link_directories(${ANTLR4_LIB_DIR})
link_libraries(${ANTLR4LIBRARY})

add_custom_command(
  OUTPUT WhileBaseListener.cpp WhileBaseListener.h WhileLexer.cpp WhileLexer.h WhileLexer.interp WhileLexer.tokens WhileListener.cpp WhileListener.h WhileParser.cpp WhileParser.h
  # Remove target directory
  COMMAND
  ${CMAKE_COMMAND} -E remove WhileBaseListener.cpp WhileBaseListener.h WhileLexer.cpp WhileLexer.h WhileLexer.interp WhileLexer.tokens WhileListener.cpp WhileListener.h WhileParser.cpp WhileParser.h
  COMMAND
  # Generate files
  ${ANTLR4_TOOL} -Dlanguage=Cpp -o ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/While.g4
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  MAIN_DEPENDENCY "src/While.g4"
)

add_executable(while-run
  src/WhileRun.cc
  src/WhileCFG.cc src/WhileInterpreter.cc
  WhileParser.cpp WhileLexer.cpp
  WhileBaseListener.cpp WhileListener.cpp
)

add_executable(while-analysis
  src/WhileAnalysis.cc
  src/WhileConstantRegisterAnalysis.cc
  src/WhileDeadCodeAnalysis.cc
  src/WhileInterproceduralFramePointerAnalysis.cc
  src/WhileCFG.cc src/WhileInterpreter.cc
  WhileParser.cpp WhileLexer.cpp
  WhileBaseListener.cpp WhileListener.cpp
  src/WhileConstantDeadAnalysis.cc
)
