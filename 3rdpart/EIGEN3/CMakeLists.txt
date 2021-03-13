message("compiler eigen current path ${CMAKE_CURRENT_LIST_DIR}")

set(EIGEN3_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/")

target_include_directories(TSUBAKI PRIVATE "${EIGEN3_INCLUDE_DIRS}")

