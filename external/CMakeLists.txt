#-------------------DEFINE ZONE----------------------#
#this library
set(LIBRARY_NAME "external")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

set(LIBRARY_SOURCES
    HyperbolicLnPlugin.cpp
)
set(LIBRARY_HEADERS

)

#include more
set(LIBRARIES_TO_LINK controller plugin)

# Add the subdirectory for output
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#----------------------------------------------------#

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
#set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
#target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries( ${LIBRARY_NAME} PUBLIC ${LIBRARIES_TO_LINK})
#
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

if(UNIX)
    set(PLUGIN_FILE plugins.pdp.unix)
elseif(WIN32)
    set(PLUGIN_FILE plugins.pdp.win)
    target_link_libraries(${HYPERBOLIC_LN_PLUGIN_TARGET} pdCalcBackend)
endif()

message(STATUS "Executable output path: ${EXECUTABLE_OUTPUT_PATH}")


#add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_SOURCE_DIR}/external/${PLUGIN_FILE}
#        ${EXECUTABLE_OUTPUT_PATH}/plugins.pdp)