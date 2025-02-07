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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <memory>

#include <doctest/doctest.h>

#include "sandbox/dummygroup/dummygroup.h"

TEST_CASE("dummy test") // NOLINT
{
  auto test = sandbox::dummygroup::DummyGroup::Make();
  const char* kText(test->GetSomething());
  CHECK(kText != nullptr); // NOLINT
}
