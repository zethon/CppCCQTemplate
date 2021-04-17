cmake_minimum_required(VERSION 3.17)

project(CppCCQtemplate)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

include(CMake/conan.cmake)
conan_cmake_run(REQUIRES
    qt/6.0.1@bincrafters/stable
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)



# # # initialize conan libs
# # include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
# # include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# # conan_basic_setup(SKIP_STD)




# # find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
# find_package(Qt6 COMPONENTS Widgets)
# # find_package(Qt6 COMPONENTS Widgets REQUIRED)
# # find_package(Qt6 COMPONENTS Widgets REQUIRED)

# set(CMAKE_AUTOMOC TRUE)
# set(CMAKE_AUTORCC TRUE)
# set(CMAKE_AUTOUIC TRUE)

add_subdirectory(src)




# set(SOURCE_FILES
#     main.cpp
# )

# set(MOC_HEADERS
# )

# set(UI_SOURCES
# )

# set(HEADER_FILES
#     ${MOC_HEADERS}
# )

# if (APPLE)
#     set(GUI_TYPE MACOSX_BUNDLE)
# elseif(WIN32)
#     set(GUI_TYPE WIN32)
# endif()

# add_executable(App ${GUI_TYPE}
#     ${SOURCE_FILES}
#     ${HEADER_FILES}
#     ${UI_FILES}
#     ${RESOURCE_FILES}
#     ${QML_FILES}
#     ${QRC_SOURCE_FILES}
# )

# target_link_libraries(App
#     PRIVATE ${CONAN_LIBS})

# # target_link_libraries(App 
# #     ${CONAN_LIBS}
# #     ${QT_MODULE_LIST}
# #     ${DEPENDENCY_LIST}
# # )