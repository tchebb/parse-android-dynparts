add_library(lp reader.cpp utility.cpp)
target_include_directories(lp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lp PRIVATE crypto)
target_compile_options(lp PRIVATE -Wall -Wextra -pedantic)
