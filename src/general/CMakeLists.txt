configure_file(general.h.in ${CMAKE_CURRENT_SOURCE_DIR}/general.h)
add_library(smoldb-general INTERFACE)
target_include_directories(smoldb-general INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
