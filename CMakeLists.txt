project(shouter)

include_directories("${PROJECT_SOURCE_DIR}/include")


add_subdirectory(lib)

add_executable(shouter main.cpp)

target_link_libraries(shouter shouter_lib)
