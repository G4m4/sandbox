/// @file implementation/main.cc
/// @brief Implementation main entry point
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

#include <cstdio>

#include "immintrin.h"

#include "sandbox/src/common.h"
#include "sandbox/src/dummygroup/dummyclass.h"

struct Toto {
  bool B;
  __m128 Vec;
  bool C;
};

/// @brief Main function, of course.
int main(int /*argc*/, char ** /*argv*/) {
  const char *kText(sandbox::dummygroup::DummyClass().DoSomething());

  printf("Done: %s", kText);

  {
    int a = 1;
    short j;
    float f = 1.f; // Originally not initialized but tis-kernel caught
    // it was being accessed w/ an indeterminate value below

    printf("%i\n", j = *(reinterpret_cast<short *>(&a)));
    printf("%i\n", *(reinterpret_cast<int *>(&f)));

    char arr[4] = {0x0F, 0x0, 0x0, 0x00};
    std::printf("%i\n", *reinterpret_cast<int *>(arr));
  }

  {
    int *x = new int[2]; // 8 bytes: [0,7].
    int *u =
        (int *)((char *)x + 6); // regardless of alignment of x this will not
    // be an aligned address
    *u = 1;             // Access to range [6-9]
    printf("%d\n", *u); // Access to range [6-9]
  }

  {
    short a[2];

    a[0] = 0x1111;
    a[1] = 0x1111;

    *(int *)a = 0x22222222; /* violation of aliasing rules */

    printf("%x %x\n", a[0], a[1]);
  }
  {
    int value[4] = {56, 57, 58, 59};
    __m128 toto = _mm_loadu_ps(reinterpret_cast<float *>(&value[0]));
    const float *ptr = reinterpret_cast<float *>(&toto);
    float tata = *ptr;
    float tata1 = *(ptr + 1);
    float tata2 = *(ptr + 2);
    float tata3 = *(ptr + 3);
    printf("%f %f %f %f", tata, tata1, tata2, tata3);
    printf("%d", value[0]);
  }
  return 0;
}
