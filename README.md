# C++ Conan CMake Qt6 Project Template

This project aims to provide examples of the following common tasks associated with a Github hosted C++ project:

* Using Qt6 with CMake and Conan
* Using Qt .ui files
* Using a custom library
* Github actions to build on Windows, Mac and Ubuntu
* A unit test environment
* Packaging and Deployment

Each item is discussed in detail.

## Project Organization


## Using Qt6 with CMake and Conan


```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
git clone https://github.com/zethon/CppCCQTemplate.git
cd CppCCQTemplate 
mkdir build && cd build
conan install .. -s build_type=Debug -g cmake_paths -g cmake_find_package -g=cmake -g deploy
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . 
```
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
