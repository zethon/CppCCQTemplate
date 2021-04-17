# CppCCQTemplate
A C++ Conan CMake Qt6 Project Template

conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

This project is a 

* Conan
* Qt 6
* UI files
* GitHub Actions

## Build

```
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

### Helpful Links

https://wiki.qt.io/Qt6_Add-on_src_package_build_using_Conan_package_manager
