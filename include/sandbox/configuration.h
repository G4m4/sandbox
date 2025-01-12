/// Provides basic preprocessor macros in order to detect
/// user variables/hardware/OS/compiler...
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

/// @brief Compiler detection
#if (defined(__GNUC__)) && !defined(__clang__) && !defined(__INTEL_COMPILER)
  #define COMPILER_GCC 1
#elif (defined(__clang__))
  #define COMPILER_CLANG 1
#elif (defined(_MSC_VER))
  #define COMPILER_MSVC 1
#else
  #error "Compiler could not be detected"
#endif

/// @brief Build configuration detection
/// Since there are no easy cross-platform way to do this,
/// we assume that "no asserts" means release
#if (defined(_NDEBUG) || defined(NDEBUG))
  #define BUILD_CONFIGURATION_DEBUG 0
#else // defined(NDEBUG) ?
  #define BUILD_CONFIGURATION_DEBUG 1
#endif // defined(NDEBUG) ?

/// @brief Architecture detection - compiler specific preprocessor macros
#if COMPILER_MSVC
  #if defined(_M_X64)
    #define ARCH_X86_64 1
  #elif defined(_M_IX86)
    #define ARCH_X86_32 1
  #endif
#elif COMPILER_GCC || COMPILER_CLANG
  #if defined(__x86_64__)
    #define ARCH_X86_64 1
  #elif (defined(__i386__))
    #define ARCH_X86_32 1
  #endif
#endif

/// @brief SIMD enabling, based on platform
#if defined(DISABLE_SIMD)
  #define USE_SSE 0
#else
  #if (ARCH_X86_32)
    #define USE_SSE 1
  #endif
#endif
#if (ARCH_X86_64)
  #define USE_SSE 1
#endif
