file(GLOB cmd_ld_SRC
  "src/*.cpp"
)
add_executable(cmd-ld ${cmd_ld_SRC})

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support core)

target_link_libraries(cmd-ld libmodifysource ${llvm_libs} libmodernjson)