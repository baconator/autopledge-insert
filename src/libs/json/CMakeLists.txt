add_library(libmodernjson STATIC include/json.hpp)
target_include_directories(libmodernjson PUBLIC include)
set_target_properties(libmodernjson PROPERTIES LINKER_LANGUAGE CXX)