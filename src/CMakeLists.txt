cmake_minimum_required(VERSION 3.5)
project(LogUtil)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Rearranger.cpp Rearranger.h LogEntry.h LogTime.cpp LogTime.h LogEntryParser.cpp LogEntryParser.h LogLine.cpp LogLine.h LogEntry.cpp json.hpp FileUtils.hpp CommandLineUtils.hpp Blocker.cpp Blocker.h TimeBlocker.cpp TimeBlocker.h LogMessageBlocker.cpp LogMessageBlocker.h RootBlocker.cpp RootBlocker.h BlockerFactory.cpp BlockerFactory.h ptr.h)
add_executable(LogUtil ${SOURCE_FILES})