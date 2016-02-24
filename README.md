SandBox
==================================

SandBox is an empty structure for fast projects setup - supported so far:
- Basic (lib + executable)
- GoogleTest
- VST plugin

It includes a basic directory structure, simple ready-mix Cmake files as well as basic git and Travis configurations.
Different configurations are available for different frameworks; each one of them resides in a different branch of this depot.

The basic configuration on the master branch creates 2 targets:
- sandbox_implementation (executable)
- sandbox_lib (static lib)

At runtime, the executable instantiates a dummy class from sandbox_lib and prints stuff in the standard output.

Please note that all this is not an attempt to waste a few kwatts in a dumb manner but hopefully a way to speed up new projects beginning.

Fast project setup
------------------

Creating a project based on SandBox template is done through a Python script:

    cd scripts
    python create_project.py ../ YOUR_PROJECT_LOCATION YOUR_PROJECT_NAME

Where YOUR_PROJET_LOCATION may be by instance "c:/dev" and YOUR_PROJECT_NAME something like "MyAwesomeProject"

A Travis configuration file is provided in order to be used with [Travis CI](https://travis-ci.org/).

The build system is based on Cmake.
Building is done with:

    mkdir build && cd build
    cmake ..
    cmake --build .

The directory hierarchy is as follows:
- sandbox
  - implementation
    - main.cc
  - src
    - common.h
    - configuration.h
    - dummygroup
      - dummyclass.cc
      - dummyclass.h

The few lines of code there strictly follows [Google Style](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml).

Branch: GoogleTest
-----

Tests rely on [Google Test Framework](http://code.google.com/p/googletest/).

All required Cmake variables are set up, and the GTest library is used as a submodule; you have to add it manually:

  git submodule add https://chromium.googlesource.com/external/googletest.git externals/gtest

Branch: Vst Plugin
-----

A basic Vst plugin implementation is available, relying on [JUCE Framework](https://github.com/julianstorer/JUCE).

All required Cmake variables are set up, and the JUCE library is used as a submodule; you have to add it manually:

  git submodule add git://github.com/julianstorer/JUCE.git externals/juce

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
