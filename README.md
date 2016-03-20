# Usage (when it's implemented ...)
Replace `clang++` or `g++` in your build with `autopledge --quiet`. Instrumented source will be saved alongside the unchanged source as `filename.autopledged.cpp`. Only the instrumented source will be compiled.

# Building
* `mkdir build`
* `cd build`
* `cmake -G "MSYS Makefiles" ../src`
* `make`

# Links
* [Paper](https://www.authorea.com/users/87525/articles/105798/_show_article?access_token=C2nWklTKKQM3vNmRBNneHw) ([github repo](https://github.com/baconator/autopledge-paper))
* Measurement tool (to be added)
* OpenBSD checkout
