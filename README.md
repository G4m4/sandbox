SandBox
==================================

SandBox is an empty structure for fast projects setup.

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

You are on the Vst Plugin branch
-----

A basic Vst plugin implementation is available, relying on [JUCE Framework](https://github.com/julianstorer/JUCE).

All required Cmake variables are set up, and the JUCE library is used as a submodule; you have to initialise it manually:

    git submodule init
    git submodule update

You will also need the [Steinberg VST SDK](http://www.steinberg.net/en/company/developers.html) - and to set an environment variable VST_ROOT to it.

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
