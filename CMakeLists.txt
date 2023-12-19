CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

PROJECT(QuickExam)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/third_party)

FIND_PACKAGE(oatpp REQUIRED)
FIND_PACKAGE(oatpp-swagger REQUIRED)
FIND_PACKAGE(oatpp-postgresql REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

ADD_EXECUTABLE(QuickExamBackend
        ${CMAKE_SOURCE_DIR}/src/QuickExamBackend.cpp)

TARGET_LINK_LIBRARIES(QuickExamBackend
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
        )