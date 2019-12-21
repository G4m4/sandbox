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

You are on the Imgui branch
-----

You will need [Qt] (https://www.qt.io/download-open-source) installed on your dev machine, including QML module.
On Debian-based distros:

    sudo dnf install qt5-qtbase-devel.x86_64 qt5-qtdeclarative-devel.x86_64

On Ubuntu-based distros:

    sudo apt-get install qt5-default qtquick1-5-dev qtdeclarative5-dev

On some systems - typically Windows - in order to keep the build system agnostic regarding Qt libraries you will need to make Cmake aware of their location:

    cmake -DCMAKE_PREFIX_PATH="C:/Qt/5.9.1/msvc2015_64/lib/cmake" ../

Where "C:/Qt/5.9.1/msvc2015_64/lib/cmake" gets to be replaced by your own.

Imgui is already set up as a submodule;

    git submodule init
    git submodule update

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
