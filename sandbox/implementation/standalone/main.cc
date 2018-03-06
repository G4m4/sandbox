/// @file implementation/main.cc
/// @brief Implementation main entry point
/// @author gm
/// @copyright gm 2016
///
/// This file is part of SandBox
///
/// SandBox is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// SandBox is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with SandBox.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>

#include "sandbox/src/common.h"
#include "sandbox/src/context/context.h"

/// @brief Main function, of course.
int main(int argc, char **argv) {
  sandbox::IGNORE(argc);
  sandbox::IGNORE(argv);

  sandbox::context::Context context;
  context.Initialize();

  do {
    context.Clear();
    context.Update();
  } while(!context.ShouldClose());

  context.Terminate();

  printf("Done.");

  return 0;
}
