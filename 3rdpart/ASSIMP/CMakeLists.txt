message("compiler assimp current path ${CMAKE_CURRENT_LIST_DIR}")

set(ASSIMP_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(ASSIMP_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Debug/assimp-vc142-mtd.lib")
    set(ASSIMP_LINK_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/Debug/")
    set(ASSIMP_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/Debug/assimp-vc142-mtd.dll")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(ASSIMP_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Release/assimp-vc142-mt.lib")
    set(ASSIMP_LINK_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/Release/")
    set(ASSIMP_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/Release/assimp-vc142-mt.dll")
endif()

target_include_directories(TSUBAKI PRIVATE ${ASSIMP_INCLUDE_DIRS} )

target_link_directories(TSUBAKI PRIVATE ${ASSIMP_LINK_DIRS} )

target_link_libraries(TSUBAKI PRIVATE ${ASSIMP_LIBRARIES} )
