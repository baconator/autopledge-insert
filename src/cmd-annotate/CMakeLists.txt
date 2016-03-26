file(GLOB cmd_annotate_SRC
  "src/*.cpp"
)
add_executable(cmd-annotate ${cmd_annotate_SRC})

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support core)

target_link_libraries(cmd-annotate libannotatesyscalls ${llvm_libs} libmodernjson)