# C++ Conan CMake Qt6 Project Template

This project aims to provide examples of the following common tasks associated with a Github hosted C++ project:

* `[x]` Using Qt6 with CMake and Conan
* `[ ]` Using Qt .ui files
* `[x]` Using a custom static library
* `[ ]` Using a custom shared library
* `[ ]` Github actions to build on Windows, Mac and Ubuntu
* `[ ]` A unit test environment
* `[ ]` Packaging and Deployment

Each item is discussed in detail.

## Project Organization


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

## Notes
### CMake, Qt, OpenSSL conflict error

As of this writing, I am using CMake 3.20.1, and when I try to run the 

```
ERROR: Conflict in cmake/3.19.1:
    'cmake/3.19.1' requires 'openssl/1.1.1i' while 'qt/6.0.1' requires 'openssl/1.1.1j'.
    To fix this conflict you need to override the package 'openssl' in your root package.
```

### Using Qt6 with Conan and CMake

The only way I could get Qt6 to work with Conan and CMake was by including the `/CMake/conan.cmake` file from: https://github.com/conan-io/cmake-conan 

I also had to make sure to use the Qt6 located at `qt/6.0.1@bincrafters/stable`. Using the resource at `qt/6.0.1` produced CMake configuration errors.

### Helpful Links

https://wiki.qt.io/Qt6_Add-on_src_package_build_using_Conan_package_manager
