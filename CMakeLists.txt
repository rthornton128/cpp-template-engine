cmake_minimum_required(VERSION 3.6)
project("HTML Template")
enable_testing()

# Value library
set(value_SOURCES src/value)
add_library(value ${value_SOURCES})

# Test program for html templates
set(template_SOURCES src/ast src/errors src/file src/item src/parser src/position src/scanner src/template src/token)
include_directories(src)
add_library(html_template ${template_SOURCES})
target_link_libraries(html_template value)
add_executable(test_template tests/test_template)
target_link_libraries(test_template html_template)
add_test(TemplateTest test_template)

# Test program for values
set(test_SOURCES tests/test_value.cpp)
add_executable(test_value ${test_SOURCES})
target_link_libraries(test_value value)
add_test(ValueTest test_value)

include(FindPkgConfig)
#set(CMAKE_CXX_STANDARD 11)

#pkg_check_modules(curl libcurl)
#pkg_check_modules(json jsoncpp)
#pkg_check_modules(yaml yaml-cpp)

# Tmp testing program
set(tmp_SOURCES tmp.cpp)
add_executable(tmp ${tmp_SOURCES})
#link_directories(${tmp_LIBRARY_DIRS} ${yaml_LIBRARY_DIRS})
#include_directories(${tmp_INCLUDE_DIRS} ${yaml_INCLUDE_DIRS})
#target_link_libraries(tmp ${yaml_LIBRARIES})

# Curl and Json test
#set(curljson_SOURCES curl_json.cpp)
#add_executable(curl_json ${curljson_SOURCES})
#link_directories(${curl_LIBRARY_DIRS} ${json_LIBRARY_DIRS})
#include_directories(${curl_INCLUDE_DIRS} ${json_INCLUDE_DIRS})
#target_link_libraries(curl_json ${curl_LIBRARIES} ${json_LIBRARIES} -lboost_regex)
