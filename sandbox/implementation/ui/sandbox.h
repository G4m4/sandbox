/// @file sandbox.h
/// @brief SandBox UI class header
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

#ifndef SANDBOX_SRC_IMPLEMENTATION_SANDBOX_H
#define SANDBOX_SRC_IMPLEMENTATION_SANDBOX_H

#include <QScopedPointer>
#include "sandbox/src/dummygroup/dummyclass.h"

class Sandbox
{
public:
  Sandbox();
  void frame();

private:
  bool show_demo_window = true;
  bool show_another_window = false;
  QScopedPointer<sandbox::dummygroup::DummyClass> dummy_class_instance_;
};

#endif // SANDBOX_SRC_IMPLEMENTATION_SANDBOX_H
