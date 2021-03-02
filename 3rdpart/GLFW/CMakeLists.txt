
message("compiler glfw current path ${CMAKE_CURRENT_LIST_DIR}")

set(GLFW_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(GLFW_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Debug/glfw3dll.lib")
    set(GLFW_LINK_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/Debug/")
    set(GLFW_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/Debug/glfw3.dll")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(GLFW_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Release/glfw3dll.lib")
    set(GLFW_LINK_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/Release/")
    set(GLFW_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/Release/glfw3.dll")
endif()

target_include_directories(TSUBAKI PRIVATE ${GLFW_INCLUDE_DIRS} )

target_link_directories(TSUBAKI PRIVATE ${GLFW_LINK_DIRS} )

target_link_libraries(TSUBAKI PRIVATE ${GLFW_LIBRARIES} )
