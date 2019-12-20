SandBox
==================================

[![Build Status](https://travis-ci.org/G4m4/sandbox.svg?branch=master)](https://travis-ci.org/G4m4/sandbox)

SandBox is an empty structure for fast projects setup - supported so far:
- Basic (lib + executable)
- GoogleTest
- VST plugin
- OpenGL
- Qt5
- Imgui

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

Branch: OpenGL
-----

A few helper libraries - [GLFW](http://www.glfw.org/) and [GLM](http://glm.g-truc.net/0.9.7/index.html) - are already set up as submodule:

    git submodule init
    git submodule update

This implementation is using GLEW, whose CMake find script requires variables to be set - the easiest way to do it is probably to set them as environment variables:

    export GLEW_INCLUDE_DIR=PATH_TO_GLEW/include
    export GLEW_LIBRARY=PATH_TO_GLEW/lib

Notice that the library this time is dynamic - this to demonstrate a proper decoupling: we want the main executable to be graphics API-agnostic, and not link with Glew for example.

Branch: Qt5
-----

You will need [Qt](https://www.qt.io/download-open-source) installed on your dev machine. On Debian-based distros:

	sudo dnf install qt5-qtbase-devel.x86_64

On Ubuntu-based distros:

	sudo apt-get install qt5-default

On some systems - typically Windows - in order to keep the build system agnostic regarding Qt libraries you will need to make Cmake aware of their location:

    cmake -DCMAKE_PREFIX_PATH="C:/Qt/5.12.6/msvc2017_64/lib/cmake" ../

Where "C:/Qt/5.12.6/msvc2017_64/lib/cmake" gets to be replaced by your own.

Branch: Imgui
------

You will need [Qt](https://www.qt.io/download-open-source) installed on your dev machine. On Debian-based distros:

	sudo dnf install qt5-qtbase-devel.x86_64 qt5-qtdeclarative-devel.x86_64

On Ubuntu-based distros:

	sudo apt-get install qt5-default qtquick1-5-dev qtscript5-dev

On some systems - typically Windows - in order to keep the build system agnostic regarding Qt libraries you will need to make Cmake aware of their location:

    cmake -DCMAKE_PREFIX_PATH="C:/Qt/5.12.6/msvc2017_64/lib/cmake" ../

Imgui is already set up as a submodule:

    git submodule init
    git submodule update

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
