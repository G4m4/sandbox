/// @file implementation/main.cc
/// @brief Implementation main entry point
/// @author gm
/// @copyright gm 2019
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
int main(int /*argc*/, char ** /*argv*/) {
  sandbox::context::Context mainContext;

  mainContext.Initialize();
  while (!mainContext.ShouldClose()) {
    mainContext.Update();
  }
  mainContext.Terminate();

  return 0;
}
