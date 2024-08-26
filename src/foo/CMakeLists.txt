#-------------------DEFINE ZONE----------------------#
#this library
set(LIBRARY_NAME "LibFoo")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

set(LIBRARY_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/foo.cc")
set(LIBRARY_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/foo.h")

#include more
set(LIBRARIES_TO_LINK )
#----------------------------------------------------#

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries( ${LIBRARY_NAME} PUBLIC ${LIBRARIES_TO_LINK})

if(${ENABLE_WARNINGS})
    target_set_warnings(
            TARGET
            ${LIBRARY_NAME}
            ENABLE
            ${ENABLE_WARNINGS}
            AS_ERRORS
            ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
            TARGET
            ${LIBRARY_NAME}
            ENABLE
            ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${LIBRARY_NAME})
endif()