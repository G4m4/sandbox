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
#include "sandbox/src/geometry/geometry.h"

/// @brief Main function, of course.
int main(int /*argc*/, char ** /*argv*/) {
  sandbox::context::Context main_context;
  sandbox::geometry::ShapeConvex shape;
  shape.Set({{3.0f, 5.0f},
             {10.0f, 10.0f},
             {50.0f, 15.0f},
             {250.0f, 50.0f},
             {350.0f, 125.0f},
             {50.0f, 150.0f},
             {20.0f, 65.0f}});

  main_context.Initialize();
  while (!main_context.ShouldClose()) {
    main_context.Clear();
    main_context.Draw(shape);
    main_context.Update();
  }
  main_context.Terminate();

  return 0;
}
