CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(QuickExam)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/third_party)

FIND_PACKAGE(oatpp REQUIRED)
FIND_PACKAGE(oatpp-swagger REQUIRED)
FIND_PACKAGE(oatpp-postgresql REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

FILE(GLOB_RECURSE UTILS_SRC ${CMAKE_SOURCE_DIR}/src/utils/*.cpp)
FILE(GLOB_RECURSE SERVICE_SRC ${CMAKE_SOURCE_DIR}/src/service/*.cpp)

ADD_EXECUTABLE(QuickExamBackend
        ${CMAKE_SOURCE_DIR}/src/QuickExamBackend.cpp
        ${UTILS_SRC}
        ${SERVICE_SRC}
        )

TARGET_LINK_LIBRARIES(QuickExamBackend
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
        )