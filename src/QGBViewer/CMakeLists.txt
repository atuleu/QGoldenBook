# this file should be seen as a -*- mode : cmake -*-

################################################################################
# FILE EXPLORATION
################################################################################
file(GLOB_RECURSE SOURCES *.c *.cpp)
file(GLOB_RECURSE HEADERS *.h *.hpp)


# get resources
file(GLOB_RECURSE RESSOURCES_QRC *.qrc )

file(GLOB_RECURSE PROTOBUF_DEF *.proto )
file(GLOB_RECURSE FORMS *.ui)  

################################################################################
# QT & Protobuf PREPROCESSING STAGE
################################################################################

# QtDesigner forms
qt4_wrap_ui(FORMS_HEADERS ${FORMS})

# Pre compilator
foreach(header_file ${HEADERS})
  set(Q_OBJECT_MACRO_FOUND )
  file(READ ${header_file} hfile )
  string(REGEX MATCH "Q_OBJECT" Q_OBJECT_MACRO_FOUND ${hfile})
  if(Q_OBJECT_MACRO_FOUND)
      list(APPEND FILE_TO_MOC ${header_file})
  endif(Q_OBJECT_MACRO_FOUND)    
endforeach(header_file ${HEADERS})

qt4_wrap_cpp(MOC_FILES ${FILE_TO_MOC})

#ressources generator
qt4_add_resources(RESSOURCES ${RESSOURCES_QRC})

################################################################################
# TARGET CONFIGURATION
################################################################################
#Qt compile flags
include(${QT_USE_FILE})
 
if(NOT CMAKE_BUILD_TYPE STREQUAL Debug)
add_definitions(-DQT_NO_DEBUG_OUTPUT -DQT_NO_WARNING_OUTPUT)
endif(NOT CMAKE_BUILD_TYPE STREQUAL Debug)

add_executable(QGBViewer ${SOURCES} ${HEADERS} ${MOC_FILES} 
                         ${FORMS_HEADERS} ${RESSOURCES} ${PROTO_SOURCES} ${PROTO_HEADERS} )


include_directories(${PROJECT_SOURCE_DIR}/src)
#add_executable(AMARSi-benchmark ${SOURCES} ${HEADERS} ${MOC_FILES} ${FORMS_HEADERS} ${RESSOURCES})

target_link_libraries(QGBViewer ${QT_LIBRARIES} QGBBase)

if(CMAKE_COMPILER_IS_GNUCXX)
set(ERROR_FLAGS "-W -Wall -Werror -ansi")
else(CMAKE_COMPILER_IS_GNUCXX)
set(ERROR_FLAGS " ")
endif(CMAKE_COMPILER_IS_GNUCXX)

#if(UNIX)
#  add_definitions(-DIS_ON_UNIX)
#endif(UNIX)


set_target_properties(QGBBase
                      PROPERTIES VERSION ${VERSION}
                                 SOVERSION ${VERSION}
                                 COMPILE_FLAGS ${ERROR_FLAGS})

################################################################################
# INSTALLATION
################################################################################

#install(TARGETS AMARSi-benchmark DESTINATION ${amarsi-bench_BIN_DIR} 
#        COMPONENT amarsi-benchmark)
