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

#include <cstring>
#include <memory>

#include "sandbox/common.h"

#include "dummygroup/dummyclass.h"

namespace sandbox
{
namespace dummygroup
{

static const char static_data[] = "Hello, World!";

DummyClass::DummyClass() : data_(new char[sizeof(static_data)])
{
    std::memcpy(data_.get(), &static_data[0], sizeof(static_data));
}

const char* DummyClass::GetSomething(void)
{
    SANDBOX_ASSERT(data_);
    return data_.get();
}

} // namespace dummygroup
} // namespace sandbox
