include_directories( ${PROJECT_SOURCE_DIR}/inc )

ADD_LIBRARY( elog STATIC ${PROJECT_SOURCE_DIR}/src/elog.cpp )

add_executable( main ${PROJECT_SOURCE_DIR}/src/main.cpp )

TARGET_LINK_LIBRARIES( main elog )
