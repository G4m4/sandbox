SandBox
==================================

SandBox is an empty structure for fast projects setup - supported so far:
- Basic (lib + executable)
- GoogleTest
- VST plugin
- OpenGL

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

The few lines of code there strictly follows [Google Style](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml).

You are on the OpenGL branch
-----

A few helper libraries - [GLFW](http://www.glfw.org/) and [GLM](http://glm.g-truc.net/0.9.7/index.html) - are already set up as submodule:
    git submodule init
    git submodule update

This implementation is using GLEW, whose CMake find script requires variables to be set - the easiest way to do it is probably to set them as environment variables:
    export GLEW_INCLUDE_DIR=PATH_TO_GLEW/include
    export GLEW_LIBRARY=PATH_TO_GLEW/lib

Notice that the library this time is dynamic - this to demonstrate a proper decoupling: we want the main executable to be graphics API-agnostic, and not link with Glew for example.

License
==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
