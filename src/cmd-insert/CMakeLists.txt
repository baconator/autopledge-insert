file(GLOB cmd_insert_SRC
  "src/*.cpp"
)
add_executable(cmd-insert ${cmd_insert_SRC})
target_link_libraries(cmd-insert libmodifysource)