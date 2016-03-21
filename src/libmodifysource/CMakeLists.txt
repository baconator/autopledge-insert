project(modifysource VERSION 0.1 LANGUAGES CXX)

file(GLOB libmodifysource_SRC
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_library(libmodifysource STATIC ${libmodifysource_SRC})
find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs core support)
target_link_libraries(libmodifysource ${llvm_libs} libmodernjson)

target_include_directories(libmodifysource PUBLIC ${PROJECT_SOURCE_DIR}/include)