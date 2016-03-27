project(libmodifysource VERSION 0.1 LANGUAGES CXX)

file(GLOB modifysource_SRC
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

file(GLOB modifysource_INCLUDE
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        )

add_library(modifysource STATIC ${modifysource_SRC} ${modifysource_INCLUDE})

find_package(LLVM REQUIRED CONFIG)

find_package(clang REQUIRED)
target_link_libraries(modifysource PRIVATE clangTooling)

target_compile_options(modifysource PUBLIC --std=c++1z ${CLANG_DEFINITIONS} ${LLVM_DEFINITIONS})


target_include_directories(modifysource PUBLIC ${PROJECT_SOURCE_DIR}/include ${CLANG_INCLUDE_DIRS})