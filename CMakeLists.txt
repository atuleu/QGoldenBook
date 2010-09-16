project(QGoldenBook CXX )


set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

find_package(QT4 REQUIRED )
find_package(Protobuf REQUIRED)



################################################################################
# Sources exploration
################################################################################


include_directories(src)

