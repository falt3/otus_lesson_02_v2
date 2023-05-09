cmake_minimum_required(VERSION 3.2)

project(ipFilter)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(nameB ip_filter)
add_executable(${nameB} main.cpp ip.cpp ip.h)
add_executable(testIp test.cpp ip.cpp ip.h)

set_target_properties(
    ${nameB} testIp PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
# target_include_directories(listIp PRIVATE 
#     "${CMAKE_BINARY_DIR}"
# )

set_target_properties(
    testIp PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

if (MSVC)
    target_compile_options(${nameB} PRIVATE /W4)
    target_compile_options(testIp PRIVATE /W4)
else ()
    target_compile_options(
        ${nameB} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        testIp PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

enable_testing()
add_test(NAME testFilterIp COMMAND testIp)