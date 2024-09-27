cmake_minimum_required(VERSION 3.13.0)

# HEY!  Need to add additional files to the project?  (cpp, header, etc)
# Scroll down to line 53 or so to see where

# TRYING TO DEPLOY?
# switch to a "release build"  then, on projects/build/build steps/details check the "package" checkbox
# so it looks like this: Build: cmake.exe --build C:/yadayada_MinGW_64_bit-Release --target all package


# Use project folder name as project name
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)   
string(REPLACE " " "_" ProjectId ${PROJECT_NAME})

project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing -Wno-narrowing")

add_executable(${PROJECT_NAME})

include_directories("utility", "third_party", "third_party/sago", "third_party/fmt/include", "third_party/googletest/include", "third_party/googletest")

target_sources(${PROJECT_NAME} PUBLIC
    ${ASSETS}
    main.cpp

    utility/mssm.cpp
    utility/mssm.h

    utility/format_helper.h

    utility/rand.h
    utility/rand.cpp

    utility/array.h
    utility/array.cpp

    # third_party/googletest/src/gtest-all.cc
    third_party/googletest/src/gtest-assertion-result.cc
    third_party/googletest/src/gtest-death-test.cc
    third_party/googletest/src/gtest-filepath.cc
    third_party/googletest/src/gtest-matchers.cc
    third_party/googletest/src/gtest-port.cc
    third_party/googletest/src/gtest-printers.cc
    third_party/googletest/src/gtest-test-part.cc
    third_party/googletest/src/gtest-typed-test.cc
    third_party/googletest/src/gtest.cc

    third_party/fmt/include/fmt/core.h
    third_party/fmt/include/fmt/color.h
    third_party/fmt/include/fmt/format.h
    third_party/fmt/include/fmt/format-inl.h

    third_party/fmt/include/fmt/args.h
    third_party/fmt/include/fmt/base.h
    third_party/fmt/include/fmt/chrono.h
    third_party/fmt/include/fmt/compile.h
    # third_party/fmt/include/fmt/os.h
    third_party/fmt/include/fmt/ostream.h
    third_party/fmt/include/fmt/printf.h
    third_party/fmt/include/fmt/ranges.h
    third_party/fmt/include/fmt/std.h
    third_party/fmt/include/fmt/xchar.h


    # third_party/fmt/src/fmt.cc
    third_party/fmt/src/format.cc
    # third_party/fmt/src/os.cc

    third_party/sago/platform_folders.cpp
    third_party/sago/platform_folders.h

    third_party/whereami.c
    third_party/whereami.h

    utility/paths.h
    utility/paths.cpp
)

set(ASSETS_SOURCE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/assets")

file(GLOB_RECURSE ASSETS "${ASSETS_SOURCE_FOLDER}/*")

# Filter values through regex
#   filter_regex({INCLUDE | EXCLUDE} <regex> <listname> [items...])
#   Element will included into result list if
#     INCLUDE is specified and it matches with regex or
#     EXCLUDE is specified and it doesn't match with regex.
# Example:
#   filter_regex(INCLUDE "(a|c)" LISTOUT a b c d) => a c
#   filter_regex(EXCLUDE "(a|c)" LISTOUT a b c d) => b d
function(filter_regex _action _regex _listname)
    # check an action
    if("${_action}" STREQUAL "INCLUDE")
        set(has_include TRUE)
    elseif("${_action}" STREQUAL "EXCLUDE")
        set(has_include FALSE)
    else()
        message(FATAL_ERROR "Incorrect value for ACTION: ${_action}")
    endif()

    set(${_listname})
    foreach(element ${ARGN})
        string(REGEX MATCH ${_regex} result ${element})
        if(result)
            if(has_include)
                list(APPEND ${_listname} ${element})
            endif()
        else()
            if(NOT has_include)
                list(APPEND ${_listname} ${element})
            endif()
        endif()
    endforeach()

    # put result in parent scope variable
    set(${_listname} ${${_listname}} PARENT_SCOPE)
endfunction()

filter_regex(EXCLUDE "\\.DS_Store" ASSETS ${ASSETS})

set(ASSET_DEST_FILES "")

# loop over assets and make sure they get copied to the executable location
foreach (FILE ${ASSETS})

    # Get the relative path from the data-folder to the particular file.
    file(RELATIVE_PATH NEW_FILE "${ASSETS_SOURCE_FOLDER}" ${FILE})

    # Get the relative path to the file.
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

    # MAC:  Set it's location inside the app package (under Resources).
    set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")

#    message("Setting property")

    if(NOT APPLE)
        set(OUTF "${CMAKE_CURRENT_BINARY_DIR}/assets/${NEW_FILE}")

        list(APPEND ASSET_DEST_FILES ${OUTF})

        get_filename_component(OUTF_DIR "${OUTF}" DIRECTORY)

#        message("Adding custom command")
        add_custom_command(
            OUTPUT "${OUTF}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTF_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FILE} ${OUTF}
            COMMENT "Copying ${FILE} to ${OUTF}"
            DEPENDS ${FILE}
            VERBATIM
        )
    endif()

    # Make sure it shows up in the IDE Assets folder
    source_group("Assets/${NEW_FILE_PATH}" FILES "${FILE}")

endforeach ()

if(NOT APPLE)
    add_custom_target(asset_dest_target
        DEPENDS
            ${ASSET_DEST_FILES}
    )

    add_dependencies(${PROJECT_NAME} asset_dest_target)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION assets)

#think more about this?
set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)


if(UNIX AND NOT APPLE)
    # not working? maybe the thing at: #look here asldfj was windows only??
    get_filename_component(GCC_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)
    find_library(LIBGCC NAMES libgcc_s.so.1 HINTS ${GCC_PATH}/../lib64)
    get_filename_component(LIBGCC_DIR ${LIBGCC} DIRECTORY)
    file(GLOB LIBGCC_ALL ${LIBGCC_DIR}/libgcc*.so.1)
    find_library(STDCPP NAMES libstdc++.so.6 HINTS ${GCC_PATH}/../lib64)
    file(GLOB STDCPP_ALL ${STDCPP}*)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS
    ${LIBGCC_ALL}
    ${STDCPP_ALL})
endif()




if(WIN32 AND NOT MSVC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll) # important!
    GET_FILENAME_COMPONENT(GCC_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)

#    foreach(RUNTIME
#        libstdc++-6.dll
#        libgcc_s_seh-1.dll
#        libwinpthread-1.dll
#        )
#        message(STATUS "Checking for ${RUNTIME}")
#        find_library(${RUNTIME}_LIB NAMES ${RUNTIME})
#        message(${${RUNTIME}_LIB})
#        message("Hey")
#        message(${RUNTIME}_LIB-FOUND)
#        if(${RUNTIME}_LIB-FOUND)
#            message(STATUS "runtime found: ${${RUNTIME}_LIB}")
#            list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${${RUNTIME}_LIB})
#        else()
#            message(STATUS "${RUNTIME} not found. Hope nothing breaks!")
#        endif()
#    endforeach()


    find_library (LIBGCC NAMES libgcc_s_seh-1 HINTS ${GCC_PATH})
    if (LIBGCC)
      message (STATUS "Found libgcc        at ${LIBGCC}")
      list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${LIBGCC})
    else ()
      message (SEND_ERROR "Could not find libgcc!")
    endif ()

    find_library (LIBSTDCPP libstdc++-6 HINTS ${GCC_PATH})
    if (LIBSTDCPP)
      message (STATUS "Found libstdc++     at ${LIBSTDCPP}")
      list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${LIBSTDCPP})
    else ()
      message (SEND_ERROR "Could not find libstdc++!")
    endif ()

    find_library (LIBWINPTHREAD libwinpthread-1 HINTS ${GCC_PATH})
    if (LIBWINPTHREAD)
      message (STATUS "Found libwinpthread at ${LIBWINPTHREAD}")
      list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${LIBWINPTHREAD})
    else ()
      message (SEND_ERROR "Could not find libwinpthread!")
    endif ()

endif()

message(STATUS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
message(STATUS ${GCC_PATH})

include( InstallRequiredSystemLibraries )


include(CPack)
