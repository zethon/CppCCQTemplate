set(SOURCE_FILES
    main.cpp
    Window1.cpp
)

set(MOC_HEADERS
    Window1.h
)

set(HEADER_FILES
    ${MOC_HEADERS}
)

set(UI_SOURCES
    Window1.ui
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

if (APPLE)
    set(GUI_TYPE MACOSX_BUNDLE)
elseif(WIN32)
    set(GUI_TYPE WIN32)
endif()

add_executable(App ${GUI_TYPE}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_SOURCES}
)

target_link_libraries(App 
    MyLib
    ${CONAN_TARGETS}
)

# install(TARGETS App RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (APPLE)
    # Since there appear to exist problems with NOT setting the RPATH when building
    # by enabling CMAKE_KEEP_RPATH and others, we just set the libs absolute paths
    # to the conan lib dir.

    function(ChangeRPath target file new)
        add_custom_command(TARGET App
                POST_BUILD COMMAND
                ${CMAKE_INSTALL_NAME_TOOL} -change @rpath/${file} ${new}/${file}
                $<TARGET_FILE:App>)
    endfunction()

    foreach(qt_lib IN LISTS CONAN_LIBS_QT)
        ChangeRPath(App lib${qt_lib}.dylib ${CONAN_LIB_DIRS_QT})
    endforeach()
endif ()
