cmake_minimum_required(VERSION 3.20)
project(diffFilesclass)

set(CMAKE_CXX_STANDARD 20)

add_executable(diffFilesclass rtklib.h datetime.hpp datetime.cpp  rtklib_constansts.h rtkcmn.c sbasMessageType.h ubxMessage.h helperFunctions.h ubxMessage.cpp helperFunctions.cpp main.cpp navigation_engine.hpp navigation_engine.cpp navigation_base.hpp)
