SandBox
==================================

SandBox is an empty structure for fast projects setup.

It includes a basic directory structure, simple ready-mix Cmake files as well as basic git and Travis configurations.
It creates 3 targets:
- sandbox_implementation (executable)
- sandbox_lib (static lib)
- sandbox_tests (executable: tests)

At runtime, the executable instantiates a dummy class from sandbox_lib and prints stuff in the standard output.
The test checks dumb thing from the library.

Please note that all this is not an attempt to waste a few kwatts in a dumb manner but hopefully a way to speed up new projects beginning.

Structure
---------

The directory hierarchy is as follows:
- sandbox
  - implementation
    main.cc
  - src
    common.h
    configuration.h
    - dummygroup
      dummyclass.cc
      dummyclass.h
  - tests
    main.cc

The few lines of code there is strictly follows [Google Style](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml).

Tests
-----

Tests rely on [Google Test Framework](http://code.google.com/p/googletest/).
All required Cmake variables are set up, the only thing to do is make the environment variable GTEST_ROOT point to GTest sources.
On Linux, this can be done as follows:

    sudo apt-get install libgtest-dev
    export GTEST_ROOT=/usr/src/gtest

Build
-----

The build system is based on Cmake.
It comes with two boolean (ON/OFF) options:
- SANDBOX_HAS_GTEST to indicate that GTest framework can be used (see above)
- SANDBOX_ENABLE_SIMD to allow use of SIMD instructions (for now SSE2 only) by setting the proper flags.

A Travis configuration file is provided in order to be used with [Travis CI](https://travis-ci.org/).

Building is done with:

    mkdir build && cd build
    cmake ..
    cmake --build .

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
