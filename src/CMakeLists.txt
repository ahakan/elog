include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(elog SHARED ${PROJECT_SOURCE_DIR}/src/elog.cpp)

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(main elog)
