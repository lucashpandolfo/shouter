set(SEXP_LIBS sexp)
add_library(configurer_lib configurer.cpp)
target_link_libraries(configurer_lib ${SEXP_LIBS})

add_library(sources_lib source.cpp sourcefifo.cpp)

add_library(log_lib log.cpp)

set(SHOUT_LIBS shout)
add_library(shouter_lib shouter.cpp)

target_link_libraries(shouter_lib log_lib sources_lib configurer_lib ${SHOUT_LIBS})