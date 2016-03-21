# Grand Plan
* Main problem: a number of libraries are linked in and not compiled at once, so information about which syscalls they make is difficult to obtain statically.
* Solution: Have a mock compiler and linker that instead output syscall-related data, then run the compilation twice (once w/o data, once with).

# Building
* `mkdir build`
* `cd build`
* `cmake -G "MSYS Makefiles" ../src`
* `make`

# Links
* [Paper](https://www.authorea.com/users/87525/articles/105798/_show_article?access_token=C2nWklTKKQM3vNmRBNneHw) ([github repo](https://github.com/baconator/autopledge-paper))
* Measurement tool (to be added)
* OpenBSD checkout
