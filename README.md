# Django_cpp
A simple Django template render in c++ 

Using [Django](https://docs.djangoproject.com/en/4.1/ref/templates/language/) language as basis language.

It would remain unrecognized token.

## Pre-requirements
```
cmake
clang++ or g++ (Not sure for MSVC)
conan
```

## How to build
```shell=
mkdir build
conan install engine/conanfile.txt -if build --build=missing
cd build
cmake  -DCMAKE_BUILD_TYPE=Release ../engine -G Ninja
ninja
```

:::detail
You should `brew install nlohmann-json` if you are using MacOS.
:::

## TODO:
- Supporting features:
    - [x] extends
    - [ ] block
    - [x] variables
        - [x] member data
        - [x] serialize
    - [ ] filters
    - [ ] tags
        - [ ] `for` statement
        - [ ] `if` statement
    - [x] comments

