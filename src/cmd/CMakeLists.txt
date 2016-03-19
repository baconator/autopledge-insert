file(GLOB cmd_SRC
  "src/*.cpp"
)
add_executable(cmd ${cmd_SRC})
target_link_libraries(cmd libmodifysource)