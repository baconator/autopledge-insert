# Grand Plan
* Use [BEAR](https://github.com/rizsotto/Bear) to generate a compilation database.
* Run an analysis over that in order to determine what capabilities are used in which symbols.
* Annotate all implicated files with the computed pledge statements.

# Usage (eventually)
* ¯\\\_(ツ)\_/¯ Just discovered bear, so lets just see what arises organically.

# Requirements (MSYS2)
* (all prefixed w/mingw-w64-x86_64-) clang, clang-tools-extra, cmake, extra-cmake-modules, gdb, make, lld

# Building
* `mkdir build`
* `cd build`
* `cmake -G "MSYS Makefiles" ../src`
* `make`

# Links
* [Paper](https://www.authorea.com/users/87525/articles/105798/_show_article?access_token=C2nWklTKKQM3vNmRBNneHw) ([github repo](https://github.com/baconator/autopledge-paper))
* [Measurement tool](https://github.com/Steven-Evans/autopledge-measure)
* [OpenBSD checkout](https://github.com/Steven-Evans/OpenBSD)
