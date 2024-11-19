/// @file common.h
/// @brief SandBox common utilities header
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

#ifndef SANDBOX_SRC_COMMON_H_
#define SANDBOX_SRC_COMMON_H_

#include <cassert>

#include "sandbox/src/configuration.h"

namespace sandbox {

/// @brief Assume that the following condition is always true
/// (on some compilers, allows optimization)
#if(COMPILER_MSVC)
  static inline void ASSUME(const bool condition) {_assume(condition);}
#elif(COMPILER_GCC) || (COMPILER_CLANG)
  static inline void ASSUME(const bool condition) {if (!(condition)) { __builtin_unreachable(); }}
#else
  #define ASSUME(_condition_)
#endif  // _COMPILER_ ?

/// @brief Asserts condition == true
#if(BUILD_CONFIGURATION_DEBUG)
  #define SANDBOX_ASSERT(_condition_) (assert((_condition_)))
#else
  // Maps to "assume" in release configuration for better optimization
  #define SANDBOX_ASSERT(_condition_) {::sandbox::ASSUME((_condition_));}
#endif

}  // namespace sandbox

#endif  // SANDBOX_SRC_COMMON_H_
