project(modifysource VERSION 0.1 LANGUAGES CXX)

file(GLOB libmodifysource_SRC
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_library(libmodifysource SHARED ${libmodifysource_SRC})

target_compile_options(libmodifysource PUBLIC --std=c++1z)

find_package(LLVM REQUIRED CONFIG)
#llvm_map_components_to_libnames(llvm_libs core support)

find_package(clang REQUIRED)
target_link_libraries(libmodifysource clangTooling)



target_include_directories(libmodifysource PUBLIC ${PROJECT_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})