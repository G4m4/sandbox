/// @file dummyclass.h
/// @brief Dummy class declaration
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

#pragma once

#include <memory>

namespace sandbox
{
namespace dummygroup
{

/// @brief Dummy class
class DummyClass
{
  public:
  DummyClass();
  ~DummyClass();
  DummyClass(const DummyClass&) = delete;
  DummyClass(DummyClass&&) = delete;
  DummyClass& operator=(const DummyClass&) = delete;
  DummyClass& operator=(DummyClass&&) = delete;

  /// @brief Outputs an "Hello, world!" into a C-style string
  const char* GetSomething(void);

  private:
  const std::unique_ptr<char[]> data_; ///< Internal class data
};

} // namespace dummygroup
} // namespace sandbox
