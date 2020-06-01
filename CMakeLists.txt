cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl")
set(CMAKE_INSTALL_LIBDIR "/usr/lib")
set(CMAKE_INSTALL_INCLUDEDIR "/usr/include")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h")

project(beatcppver VERSION 0.0.1 DESCRIPTION "BeatSaver API Wrapper for C++")

find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

include(GNUInstallDirs)
add_library(beatcppver SHARED ${SOURCE_FILES})
add_executable(tst_beatcppver test/tst_bs.cpp ${SOURCE_FILES})

configure_file(beatcppver.pc.in beatcppver.pc @ONLY)

include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LIBRARIES})

set_target_properties(beatcppver PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(beatcppver PROPERTIES SOVERSION 0)

set_target_properties(beatcppver PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
target_link_libraries(beatcppver PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(beatcppver PRIVATE src)
target_include_directories(tst_beatcppver PRIVATE src)
target_include_directories(tst_beatcppver PRIVATE test)

install(TARGETS beatcppver LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/beatcppver.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
