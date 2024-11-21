/// @file dummyclass.cc
/// @brief Dummy class definition
/// @author gm
/// @copyright gm
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

#include "sandbox/src/dummygroup/dummyclass.h"
#include "sandbox/src/common.h"

namespace sandbox {
namespace dummygroup {

const char DummyClass::data_[] = "Hello, World!";

DummyClass::DummyClass() {
  // Nothing to do here for now
}

DummyClass::~DummyClass() {
  // Nothing to do here for now
}

const char *DummyClass::DoSomething(void) { return &data_[0]; }

} // namespace dummygroup
} // namespace sandbox
