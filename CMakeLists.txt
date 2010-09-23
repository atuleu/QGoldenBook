project(QGoldenBook CXX C)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

find_package(Qt4 REQUIRED )
set(QT_USE_QTNETWORK 1)

#find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})


################################################################################
# Sources exploration
################################################################################


add_subdirectory(src)
