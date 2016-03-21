file(GLOB cmd_c_SRC
  "src/*.cpp"
)
add_executable(cmd-c ${cmd_c_SRC})

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support core)

target_link_libraries(cmd-c libmodifysource ${llvm_libs} libmodernjson)