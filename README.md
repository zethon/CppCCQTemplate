# C++ Conan CMake Qt6 Project Template

![Windows Workflow](https://github.com/zethon/CppCCQTemplate/actions/workflows/windows.yml/badge.svg)
![macos Workflow](https://github.com/zethon/CppCCQTemplate/actions/workflows/macos.yml/badge.svg)
![Ubuntu Workflow](https://github.com/zethon/CppCCQTemplate/actions/workflows/ubuntu.yml/badge.svg)


This project aims to provide examples of the following common tasks with C++ projects hosted on Github:

* `[x]` Using Qt6 with CMake and Conan
* `[ ]` Using Qt .ui files
* `[x]` Using a custom static library
* `[ ]` Using a custom shared library
* `[x]` Github actions to build on Windows, Mac and Ubuntu
* `[ ]` A unit test environment
* `[ ]` Packaging and Deployment

Each item is discussed in detail.
## Using Qt6 with CMake and Conan

First we clone the Github repository:

```
git clone https://github.com/zethon/CppCCQTemplate.git
```

Then create a build folder inside of the repository's folder and navigate into it:

```
cd CppCCQTemplate && mkdir build && cd build
```

At this point we're ready to run CMake, which in turn runs Conan. However, the bintray repository used to download Qt6 may not be configured on the local machine. It can be added to the Conan remote cache with the following command:

```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

Once we've added the bincrafters repository, we can run Conan and CMake in one step: 

```
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

In this case we have configured our build system to compile debug versions of the binaries. Now we can build with the following command:

```
cmake --build .
```

## Using a custom library

The library is called `MyLib` is exists in `src/MyLib`. The `App` project statically links to it.

Even though no linking is actually done when builing the library by itself, this line must still be included in the library's CMake file:

```
target_link_libraries(MyLib PRIVATE
    Qt6::Core
)
```

Without this the compiler complains that it cannot find `QString` on the line: `#include <QString>`.

## Github Actions

THe Github action settings for Windows was pretty straightforward. So much so that it almost worked right away, and thus there are no notes worth mentioning.
### macos

I had to make sure the latest version of CMake is installed, which was luckly a simple call to brew (even though this didn't work on my local Mac). 

### Ubuntu

I could only get Qt6 to build on Github Actions if I used `ubuntu-latest`, which is fine. At one point when I was trying to get it to work I had switched to `ubuntu-18.06`, but once I got past the initial error that caused me to switch, I got a GLIB compatibility error that lead me to [this Stack Overflow post](https://stackoverflow.com/questions/64495774/libcrypto-so-undefined-reference-to-fcntlglibc-2-28). 

I had forgotten to add the bincrafters repo, but the error I was getting said something like "could not find Qt/6.0.1@bincrafters/stable in repos", which made it sound like the Qt6 library wasn't in the repo. I would have instead expected something like "unknown repo".

And lastly, I had to make sure that the `libgl1-mesa-dev` library was installed on the build image. 

## Notes
### CMake, Qt, OpenSSL conflict error

As of this writing, I am using CMake 3.20.1. This version is required for the CMake functionality I'm using to download Qt (discussed below). However, this lead to a rather annoying error that I've figured out how to fix but still don't quite understand:

```
ERROR: Conflict in cmake/3.19.1:
    'cmake/3.19.1' requires 'openssl/1.1.1i' while 'qt/6.0.1' requires 'openssl/1.1.1j'.
    To fix this conflict you need to override the package 'openssl' in your root package.
```

I saw this error about "Conflict in cmake/3.xx" in another project and simply had to override the library in question, which in this case is openssl. However I still do not understand why CMake has **any** requirement, much less one that is causing an **error**. 

Anyway, this error is the reason you see this in the CMakeLists.txt file:

```
conan_cmake_run(REQUIRES
    qt/6.0.1@bincrafters/stable
    openssl/1.1.1j
    ...
```
### Using Qt6 with Conan and CMake

The only way I could get Qt6 to work with Conan and CMake was by including the `/CMake/conan.cmake` file from: https://github.com/conan-io/cmake-conan 

I also had to make sure to use the Qt6 located at `qt/6.0.1@bincrafters/stable`. Using the resource at `qt/6.0.1` produced CMake configuration errors.

### Helpful Links

https://wiki.qt.io/Qt6_Add-on_src_package_build_using_Conan_package_manager
