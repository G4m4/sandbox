SandBox
==================================

[![pipeline status](https://lab.frogg.it/machinmachines/sandbox/badges/master/pipeline.svg)](https://lab.frogg.it/machinmachines/sandbox/-/commits/master)

SandBox is an empty structure for fast projects setup - supported so far:

- Basic (lib + executable)
- DocTest
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

A GitLab configuration file is provided.

The build system is based on Cmake.
Building is done with:

    mkdir build && cd build
    cmake ..
    cmake --build .

The few lines of code there strictly follows [Google Style](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml).

You are on the Imgui branch
-----

### Desktop build

We use the GLFW Vulkan implementation.
You will need the [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) installed on your dev machine.

### Android build

We use the OpenGL 3 (ES) implementation.
You will need the [Android SDK](https://developer.android.com/tools) installed on your machine, and feed it to Cmake, for instance through the CMakeUserPresets.json file:

```json,
    {
      "name": "local-android",
      "inherits": [
        "local",
        "android"
      ],
      "cacheVariables": {
        "ANDROID_PLATFORM": "android-35",
        "CMAKE_FIND_ROOT_PATH_MODE_PACKAGE": "BOTH",
        "CMAKE_TOOLCHAIN_FILE": "PATH_TO_ANDROID_NDK/NDK_VERSION/build/cmake/android.toolchain.cmake"
      },
      "environment": {
        "JAVA_HOME": "PATH_TO_JAVA_RUNTIME"
      }
    }
```

License

==================================
SandBox is under GPLv3.

See the COPYING file for the full license text.
