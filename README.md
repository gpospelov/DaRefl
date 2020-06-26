# DaRefl: reflectometry simulations

This is a prototype of the simulation software for reflectometry.
It is a part of [BornAgain project](https://www.bornagainproject.org)

## Requirements

+ C++-17
+ CMake 3.14
+ Qt 5.12

## Installation instructions

```
git clone --recurse-submodules  https://github.com/gpospelov/DaRefl
mkdir <build-dir>; cd <build-dir>
cmake <source>; make -j8; ctest

# run the GUI
<build-dir>/bin/darefl
```

