# C++ Conan CMake Qt6 Project Template

![Windows Workflow](https://github.com/zethon/CppCCQTemplate/actions/workflows/windows.yml/badge.svg)
![macos Workflow](https://github.com/zethon/CppCCQTemplate/actions/workflows/macos.yml/badge.svg)
![Ubuntu Workflow](https://github.com/zethon/CppCCQTemplate/actions/workflows/ubuntu.yml/badge.svg)
[![codecov](https://codecov.io/gh/zethon/CppCCQTemplate/branch/master/graph/badge.svg?token=C2ybTeKtDB)](https://codecov.io/gh/zethon/CppCCQTemplate)


This project aims to provide examples of the following common tasks with C++ projects hosted on Github:

* `[x]` Using Qt6 with CMake and Conan
* `[x]` Using a custom static library
* `[x]` Github actions to build on Windows, Mac and Ubuntu
* `[x]` A unit test environment
* `[x]` Code coverage
* `[ ]` Using Qt .ui files
<!--
* `[ ]` Using a custom shared library
* `[ ]` Packaging and Deployment
-->

Each item is discussed in detail.

## Building

First we clone the Github repository:

```bash
git clone https://github.com/zethon/CppCCQTemplate.git
```

Then create a build folder inside of the repository's folder and navigate into it:

```bash
cd CppCCQTemplate && mkdir build && cd build
```

At this point we're ready to run CMake, which in turn runs Conan. However, the bintray repository used to download Qt6 may not be configured on the local machine. It can be added to the Conan remote cache with the following command:

```bash
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

Once we've added the bincrafters repository, we can run Conan and CMake in one step: 

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

In this case we have configured our build system to compile debug versions of the binaries. Now we can build with the following command:

```bash
cmake --build .
```

<hr/>

## Using Qt6 with CMake and Conan

The only way I could get Qt6 to work with Conan and CMake was by including the `/CMake/conan.cmake` file from: https://github.com/conan-io/cmake-conan However, in order to use that file I had to use CMake 3.20.1. 

I also had to make sure to use the Qt6 located at `qt/6.0.1@bincrafters/stable`. Using the resource at `qt/6.0.1` produced CMake configuration errors.

One problem I ran into was this error that I still don't understand:

```bash
ERROR: Conflict in cmake/3.19.1:
    'cmake/3.19.1' requires 'openssl/1.1.1i' while 'qt/6.0.1' requires 'openssl/1.1.1j'.
    To fix this conflict you need to override the package 'openssl' in your root package.
```

I saw this error about "Conflict in cmake/3.xx" in another project and simply had to override the library in question, which in this case is openssl. However I still do not understand why CMake has **any** requirement, much less one that is causing an **error**. 

To fix it I had to specify the version of OpenSSL I wanted to use in the root *CMakeLists.txt*:


```cmake
conan_cmake_run(REQUIRES
    qt/6.0.1@bincrafters/stable
    openssl/1.1.1k
    ...
```


## Using a custom library

The library is called `MyLib` it exists in `src/MyLib`. The `App` project statically links to it.

Even though no linking is actually done when builing the library by itself, this line must still be included in the library's CMake file:

```cmake
target_link_libraries(MyLib PRIVATE
    Qt6::Core
)
```

Without this the compiler complains that it cannot find `QString` on the line `#include <QString>`.

## Github Actions

THe Github action settings for Windows was pretty straightforward. So much so that it almost worked right away, and thus there are no notes worth mentioning.

### macos

I had to make sure the latest version of CMake is installed, which was luckly a simple call to brew (even though this didn't work on my local Mac). 

### Ubuntu

I could only get Qt6 to build on Github Actions if I used `ubuntu-latest`. I also hit a GLIB compatibility error that lead me to [this Stack Overflow post](https://stackoverflow.com/questions/64495774/libcrypto-so-undefined-reference-to-fcntlglibc-2-28). 

I had forgotten to add the bincrafters repo, but the error I was getting said something like "could not find Qt/6.0.1@bincrafters/stable in repos", which made it sound like the Qt6 library wasn't in the repo. I would have instead expected something like "unknown repo".

And lastly, I had to make sure that the `libgl1-mesa-dev` library was installed on the build image.

## Adding Unit Tests

The unit tests were pretty straight forward. The only OS that gave me much trouble was Windows.

### Windows

First, I had to add the build type to the `ctest` command. Secondly for the tests to run I had to make sure that the Qt DLLs were in the test machine's path adding this in *test/CMakeLists.txt*: 

```cmake
if (WIN32)
    set_tests_properties(testMain 
        PROPERTIES
        ENVIRONMENT "PATH=${CONAN_BIN_DIRS_QT}\;$ENV{PATH}"
    )
endif()
```

## Code Coverage

Code coverage is only supported on macos. I found useful reference projects [here](https://github.com/codecov/cpp-11-standard) and [here](https://github.com/codecov/example-cpp11-cmake). 

Instead of creating a new `.yml` workflow, I tacked this onto the existing `macos.yml` by adding another matrix variable of on/off with coverage and exluding a Release build with coverage turned on. 

I did encounter this warning in the logs:

```
->  Issue detecting commit SHA. Please run actions/checkout with fetch-depth > 1 or set to 0
    project root: /Users/runner/work/CppCCQTemplate/CppCCQTemplate
```

Which I fixed by increasing the `fetch-depth` in my checkout step in `macos.yml`.

## Qt UI File

Adding support for the UI file was simple. The only real thing of note with this was that changes to the .ui file alone will not trigger the auto UIC. Instead I had to touch the corresponsing header or source files. 

<!--
### Helpful Links

https://wiki.qt.io/Qt6_Add-on_src_package_build_using_Conan_package_manager
-->
