message("compiler eigen current path ${CMAKE_CURRENT_LIST_DIR}")

set(STB_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/")

target_include_directories(TSUBAKI PRIVATE "${STB_INCLUDE_DIRS}")

