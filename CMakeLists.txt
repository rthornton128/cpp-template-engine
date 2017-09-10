cmake_minimum_required(VERSION 3.6)
project("HTML Template")
enable_testing()

# Value library
set(value_SOURCES src/value.cpp include/value.hpp)
add_library(value ${value_SOURCES})

# Template library
set(template_HEADERS include/ast include/errors include/file include/item include/parser include/position include/scanner include/template include/token)
set(template_SOURCES src/ast src/errors src/file src/item src/parser src/position src/scanner src/template src/token)
include_directories(include)
add_library(html_template ${template_SOURCES} ${template_HEADERS})
target_link_libraries(html_template value)

# Test program for position
add_executable(test_position tests/test_position.cpp)
target_link_libraries(test_position html_template)
add_test(TemplateTest test_position)

# Test program for errors
add_executable(test_errors tests/test_errors.cpp)
target_link_libraries(test_errors html_template)
add_test(TemplateTest test_errors)

# Test program for scanner
add_executable(test_scanner tests/test_scanner.cpp)
target_link_libraries(test_scanner html_template)
add_test(TemplateTest test_scanner)

# Test program for html templates
add_executable(test_template tests/test_template)
target_link_libraries(test_template html_template)
add_test(TemplateTest test_template)

# Test program for values
set(test_SOURCES tests/test_value.cpp tests/assert.hpp)
add_executable(test_value ${test_SOURCES})
target_link_libraries(test_value value)
add_test(ValueTest test_value)

# Test file
add_executable(test_file tests/test_file.cpp)
target_link_libraries(test_file html_template)
add_test(TemplateTest test_file)
