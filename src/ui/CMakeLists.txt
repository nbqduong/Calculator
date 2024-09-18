#-------------------DEFINE ZONE----------------------#
#this library
set(LIBRARY_NAME "ui")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

set(LIBRARY_SOURCES
        LookAndFeel.cpp
        CommandButton.cpp
        InputWidget.cpp
        Display.cpp
        GuiModel.cpp
        MainWindow.cpp
)
set(LIBRARY_HEADERS
        LookAndFeel.h
        CommandButton.h
        InputWidget.h
        Display.h
        GuiModel.h
        MainWindow.h
        UserInterface.h
)

#include more
set(CMAKE_PREFIX_PATH "/home/duong/Qt/6.7.2/gcc_64")

set(LIBRARIES_TO_LINK stack utilities Qt6::Widgets Qt6::Core fmt)

#target_sources(${LIBRARY_NAME} PRIVATE InputWidget.h)
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


#qt_add_moc(MyQtApp CommandButton.h)