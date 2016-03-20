file(GLOB cmd_insert_SRC
  "src/*.cpp"
)
add_executable(cmd-insert ${cmd_insert_SRC})

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support core)

target_link_libraries(cmd-insert libmodifysource ${llvm_libs})