cmake_minimum_required(VERSION 2.8)
project(testrunner)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

set(SOURCE_FILES
	./tests/BanknoteTest.cpp
	./tests/CurrencyTest.cpp
	./tests/NominalsTest.cpp
	./tests/TestRunner.cpp
	./tests/WadTest.cpp)

add_executable(testrunner ${SOURCE_FILES})
