message("compier glad current path ${CMAKE_CURRENT_LIST_DIR}")

set(GLAD_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/")

target_include_directories(TSUBAKI PRIVATE "${GLAD_INCLUDE_DIRS}")

