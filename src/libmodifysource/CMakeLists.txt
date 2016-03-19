project(modifysource VERSION 0.1 LANGUAGES CXX)

file(GLOB libmodifysource_SRC
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_library(libmodifysource STATIC ${libmodifysource_SRC})

target_include_directories(libmodifysource PUBLIC ${PROJECT_SOURCE_DIR}/include)