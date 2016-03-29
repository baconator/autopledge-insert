project(annotatesyscalls VERSION 0.1 LANGUAGES CXX)

file(GLOB libannotatesyscalls_SRC
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

file(GLOB libannotatesyscalls_INCLUDE
        "${PROJECT_SOURCE_DIR}/include/*.hpp")

add_library(libannotatesyscalls STATIC ${libannotatesyscalls_SRC} ${libannotatesyscalls_INCLUDE})
find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs core support)
target_link_libraries(libannotatesyscalls ${llvm_libs})
target_compile_options(libannotatesyscalls PUBLIC --std=c++1z ${CLANG_DEFINITIONS} ${LLVM_DEFINITIONS})

target_include_directories(libannotatesyscalls PUBLIC ${PROJECT_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})