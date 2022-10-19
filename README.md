# Django_cpp
A simple Django template render in c++ 

Using [Django](https://docs.djangoproject.com/en/4.1/ref/templates/language/) language as basis language.

It would remain unrecognized token.

## How to build
```shell=
mkdir build
conan install engine/conanfile.txt -if build --build=missing
cd build
cmake  -DCMAKE_BUILD_TYPE=Release ../engine -G Ninja
ninja
```

## TODO:
- Supporting features:
    - [ ] extends
    - [ ] block
    - [ ] variables
        - [ ] member data
        - [ ] serialize
    - [ ] filters
    - [ ] tags
        - [ ] `for` statement
        - [ ] `if` statement
    - [x] comments

