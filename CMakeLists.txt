cmake_minimum_required(VERSION 2.8)
project(banknote)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	./tests/BanknoteTest.cpp
	./tests/CurrencyTest.cpp
	./tests/NominalsTest.cpp
	./tests/TestRunner.cpp
	./tests/WadTest.cpp)

add_executable(banknote ${SOURCE_FILES})
