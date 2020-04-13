SandBox
==================================

[![Build Status](https://travis-ci.org/G4m4/sandbox.svg?branch=sfml)](https://travis-ci.org/G4m4/sandbox)

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

You are on the SFML branch
------

You will need [SFML](https://www.sfml-dev.org) dependencies installed on your dev machine. On Debian-based distros:

	sudo dnf install freetype-devel.x86_64 systemd-devel.x86_64 openal-soft-devel.x86_64 libvorbis-devel.x86_64 flac-devel.x86_64

On Ubuntu-based distros:

	sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev

We also rely on [Dear Imgui](https://github.com/ocornut/imgui) as a debug UI, using the [imgui-SFML](https://github.com/eliasdaler/imgui-sfml) binding.

SFML, imgui and imgui-SFML are already set up as submodules:

    git submodule init
    git submodule update

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
