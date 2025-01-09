/// @file dummygroup.h
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

/// @brief Base class for dummies
class DummyClassBase
{
public:
    DummyClassBase() = default;
    virtual ~DummyClassBase() = default;
    DummyClassBase(const DummyClassBase&) = delete;
    DummyClassBase(DummyClassBase&&) = delete;
    DummyClassBase& operator=(const DummyClassBase&) = delete;
    DummyClassBase& operator=(DummyClassBase&&) = delete;

    /// @brief Outputs a C-style string
    virtual const char* GetSomething(void) = 0;
};

/// @brief Dummy group module, main entry point
class DummyGroup
{
public:
    static std::unique_ptr<DummyClassBase> Make();
};

} // namespace dummygroup
} // namespace sandbox
