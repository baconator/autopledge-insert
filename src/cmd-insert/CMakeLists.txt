file(GLOB cmd_insert_SRC
  "src/*.cpp"
)
add_executable(cmd-insert ${cmd_insert_SRC})

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support core)

find_package(clang REQUIRED)

target_compile_options(cmd-insert PUBLIC --std=c++1z --std=c++1z ${CLANG_DEFINITIONS} ${LLVM_DEFINITIONS})
target_link_libraries(cmd-insert modifysource ${llvm_libs} clangTooling)