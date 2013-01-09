project(shouter)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SHOUT_LIBS shout)
set(SEXP_LIBS sexp)

add_subdirectory(lib)

add_executable(shouter main.cpp)

target_link_libraries(shouter streams_lib shouter_lib ${SHOUT_LIBS} ${SEXP_LIBS})
