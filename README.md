# DaRefl: reflectometry simulations

[![Linux](https://github.com/gpospelov/DaRefl/workflows/Linux/badge.svg?branch=master)](https://github.com/gpospelov/DaRefl/actions?query=workflow%3ALinux)
[![Windows](https://github.com/gpospelov/DaRefl/workflows/Windows/badge.svg?branch=master)](https://github.com/gpospelov/DaRefl/actions?query=workflow%3AWindows)
[![Mac OS](https://github.com/gpospelov/DaRefl/workflows/MacOS/badge.svg?branch=master)](https://github.com/gpospelov/DaRefl/actions?query=workflow%3AMacOS)
![](https://tokei.rs/b1/github/gpospelov/DaRefl/?category=code)


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

