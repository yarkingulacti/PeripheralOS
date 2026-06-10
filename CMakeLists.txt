cmake_minimum_required(VERSION 3.25)

project(
        PeripheralOS
        VERSION 0.2.0
        DESCRIPTION "Cross-platform peripheral management platform"
        HOMEPAGE_URL "https://github.com/yarkingulacti/peripheralos"
        LANGUAGES CXX
)

set(PERIPHERALOS_NAME "PeripheralOS")
set(PERIPHERALOS_EXECUTABLE_NAME "peripheralos")
set(PERIPHERALOS_AUTHOR "Yarkın Gülaçtı")
set(PERIPHERALOS_VENDOR "Yarkın Gülaçtı")
set(PERIPHERALOS_LICENSE "MIT")
set(PERIPHERALOS_IDENTIFIER "com.yarkingulacti.peripheralos")
set(PERIPHERALOS_VERSION_SUFFIX "alpha")
set(PERIPHERALOS_VERSION_FULL "${PROJECT_VERSION}-${PERIPHERALOS_VERSION_SUFFIX}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(PERIPHERALOS_BUILD_TESTS "Build tests" OFF)
option(PERIPHERALOS_BUILD_CLI "Build CLI executable" ON)
option(PERIPHERALOS_ENABLE_LTO "Enable LTO for Release builds" ON)
option(PERIPHERALOS_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

option(PERIPHERALOS_ENABLE_LOGGING "Enable logging" ON)
option(PERIPHERALOS_ENABLE_HID "Enable HID support" ON)
option(PERIPHERALOS_ENABLE_RGB "Enable RGB support" ON)
option(PERIPHERALOS_ENABLE_PROFILES "Enable profile system" ON)

option(PERIPHERALOS_BUILD_DAEMON "Build background daemon" OFF)
option(PERIPHERALOS_BUILD_UI "Build Qt UI" OFF)

set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
        Debug
        Release
        RelWithDebInfo
        MinSizeRel
)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if (WIN32)
    set(PERIPHERALOS_PLATFORM "Windows")
elseif (APPLE)
    set(PERIPHERALOS_PLATFORM "macOS")
elseif (UNIX)
    set(PERIPHERALOS_PLATFORM "Linux")
else ()
    set(PERIPHERALOS_PLATFORM "Unknown")
endif ()

set(PERIPHERALOS_SOURCES
        src/main.cpp
        src/devices/DeviceIdentity.cpp
        src/logitech/Hidpp20Client.cpp
        src/logitech/HidppBattery.cpp
)

if (UNIX AND NOT APPLE)
    list(APPEND PERIPHERALOS_SOURCES
            src/platform/linux/LinuxHidDiscovery.cpp
            src/platform/linux/LinuxHidDevice.cpp
    )
endif ()

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_Declare(
        fmt
        URL https://github.com/fmtlib/fmt/releases/download/10.2.1/fmt-10.2.1.zip
)

FetchContent_MakeAvailable(nlohmann_json fmt)

find_package(Git QUIET)

if (GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE PERIPHERALOS_GIT_COMMIT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )
else ()
    set(PERIPHERALOS_GIT_COMMIT "unknown")
endif ()

if (PERIPHERALOS_BUILD_CLI)
    add_executable(${PERIPHERALOS_EXECUTABLE_NAME}
            ${PERIPHERALOS_SOURCES}
    )

    target_include_directories(${PERIPHERALOS_EXECUTABLE_NAME}
            PRIVATE
            "${PROJECT_SOURCE_DIR}/include"
    )

    target_compile_features(${PERIPHERALOS_EXECUTABLE_NAME}
            PRIVATE
            cxx_std_20
    )

    target_link_libraries(${PERIPHERALOS_EXECUTABLE_NAME}
            PRIVATE
            nlohmann_json::nlohmann_json
            fmt::fmt
    )

    target_compile_definitions(${PERIPHERALOS_EXECUTABLE_NAME}
            PRIVATE
            PERIPHERALOS_NAME="${PERIPHERALOS_NAME}"
            PERIPHERALOS_AUTHOR="${PERIPHERALOS_AUTHOR}"
            PERIPHERALOS_VENDOR="${PERIPHERALOS_VENDOR}"
            PERIPHERALOS_LICENSE="${PERIPHERALOS_LICENSE}"
            PERIPHERALOS_IDENTIFIER="${PERIPHERALOS_IDENTIFIER}"
            PERIPHERALOS_VERSION="${PROJECT_VERSION}"
            PERIPHERALOS_VERSION_FULL="${PERIPHERALOS_VERSION_FULL}"
            PERIPHERALOS_GIT_COMMIT="${PERIPHERALOS_GIT_COMMIT}"
            PERIPHERALOS_PLATFORM="${PERIPHERALOS_PLATFORM}"
            PERIPHERALOS_ENABLE_LOGGING=$<BOOL:${PERIPHERALOS_ENABLE_LOGGING}>
            PERIPHERALOS_ENABLE_HID=$<BOOL:${PERIPHERALOS_ENABLE_HID}>
            PERIPHERALOS_ENABLE_RGB=$<BOOL:${PERIPHERALOS_ENABLE_RGB}>
            PERIPHERALOS_ENABLE_PROFILES=$<BOOL:${PERIPHERALOS_ENABLE_PROFILES}>
    )

    if (WIN32)
        target_compile_definitions(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                PERIPHERALOS_PLATFORM_WINDOWS=1
        )

        target_link_libraries(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                setupapi
                hid
                user32
        )
    elseif (APPLE)
        target_compile_definitions(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                PERIPHERALOS_PLATFORM_MACOS=1
        )

        find_library(IOKIT_FRAMEWORK IOKit REQUIRED)
        find_library(COREFOUNDATION_FRAMEWORK CoreFoundation REQUIRED)

        target_link_libraries(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                ${IOKIT_FRAMEWORK}
                ${COREFOUNDATION_FRAMEWORK}
        )
    elseif (UNIX)
        target_compile_definitions(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                PERIPHERALOS_PLATFORM_LINUX=1
        )

        find_package(PkgConfig REQUIRED)
        pkg_check_modules(UDEV REQUIRED libudev)

        target_include_directories(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                ${UDEV_INCLUDE_DIRS}
        )

        target_link_libraries(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                ${UDEV_LIBRARIES}
        )
    endif ()

    if (MSVC)
        target_compile_options(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                /W4
                /permissive-
                /Zc:__cplusplus
        )

        if (PERIPHERALOS_WARNINGS_AS_ERRORS)
            target_compile_options(${PERIPHERALOS_EXECUTABLE_NAME} PRIVATE /WX)
        endif ()
    else ()
        target_compile_options(${PERIPHERALOS_EXECUTABLE_NAME}
                PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wconversion
                -Wsign-conversion
        )

        if (PERIPHERALOS_WARNINGS_AS_ERRORS)
            target_compile_options(${PERIPHERALOS_EXECUTABLE_NAME} PRIVATE -Werror)
        endif ()
    endif ()

    if (PERIPHERALOS_ENABLE_LTO)
        include(CheckIPOSupported)
        check_ipo_supported(RESULT PERIPHERALOS_IPO_SUPPORTED OUTPUT PERIPHERALOS_IPO_ERROR)

        if (PERIPHERALOS_IPO_SUPPORTED)
            set_property(
                    TARGET ${PERIPHERALOS_EXECUTABLE_NAME}
                    PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
            )
        else ()
            message(WARNING "IPO/LTO is not supported: ${PERIPHERALOS_IPO_ERROR}")
        endif ()
    endif ()
endif ()

include(GNUInstallDirs)

if (PERIPHERALOS_BUILD_CLI)
    install(
            TARGETS ${PERIPHERALOS_EXECUTABLE_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif ()

if (PERIPHERALOS_BUILD_TESTS)
    enable_testing()

    FetchContent_Declare(
            doctest
            URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.zip
    )

    FetchContent_MakeAvailable(doctest)

    add_executable(peripheralos-tests
            tests/main.test.cpp
    )

    target_compile_features(peripheralos-tests PRIVATE cxx_std_20)

    target_link_libraries(peripheralos-tests
            PRIVATE
            doctest::doctest
    )

    add_test(NAME peripheralos-tests COMMAND peripheralos-tests)
endif ()

set(CPACK_PACKAGE_NAME "${PERIPHERALOS_NAME}")
set(CPACK_PACKAGE_VENDOR "${PERIPHERALOS_VENDOR}")
set(CPACK_PACKAGE_VERSION "${PERIPHERALOS_VERSION_FULL}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_PACKAGE_CONTACT "Yarkın Gülaçtı")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

if (WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif (APPLE)
    set(CPACK_GENERATOR "TGZ")
elseif (UNIX)
    set(CPACK_GENERATOR "TGZ")
endif ()

include(CPack)

message(STATUS "")
message(STATUS "PeripheralOS Configuration")
message(STATUS "--------------------------------")
message(STATUS "Name:                 ${PERIPHERALOS_NAME}")
message(STATUS "Version:              ${PERIPHERALOS_VERSION_FULL}")
message(STATUS "Git commit:           ${PERIPHERALOS_GIT_COMMIT}")
message(STATUS "Author:               ${PERIPHERALOS_AUTHOR}")
message(STATUS "License:              ${PERIPHERALOS_LICENSE}")
message(STATUS "Platform:             ${PERIPHERALOS_PLATFORM}")
message(STATUS "Build type:           ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard:         C++${CMAKE_CXX_STANDARD}")
message(STATUS "Build CLI:            ${PERIPHERALOS_BUILD_CLI}")
message(STATUS "Build daemon:         ${PERIPHERALOS_BUILD_DAEMON}")
message(STATUS "Build UI:             ${PERIPHERALOS_BUILD_UI}")
message(STATUS "Build tests:          ${PERIPHERALOS_BUILD_TESTS}")
message(STATUS "Enable HID:           ${PERIPHERALOS_ENABLE_HID}")
message(STATUS "Enable RGB:           ${PERIPHERALOS_ENABLE_RGB}")
message(STATUS "Enable profiles:      ${PERIPHERALOS_ENABLE_PROFILES}")
message(STATUS "Enable LTO:           ${PERIPHERALOS_ENABLE_LTO}")
message(STATUS "Warnings as errors:   ${PERIPHERALOS_WARNINGS_AS_ERRORS}")
message(STATUS "--------------------------------")
message(STATUS "")
