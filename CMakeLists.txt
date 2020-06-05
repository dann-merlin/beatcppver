cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
if(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl")
endif(UNIX)
set(CMAKE_INSTALL_LIBDIR "/usr/lib")
set(CMAKE_INSTALL_INCLUDEDIR "/usr/include")
set(BUILD_TEST OFF CACHE BOOL "Whether cmake should also build the test")

set(BEATCPPVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/beatcppver.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/bs_curl.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/bs_search.cpp" )
set(BEATCPPVER_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/beatcppver.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/bs_curl.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/bs_search.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/bs_song.h" )

project(beatcppver VERSION 0.0.1 DESCRIPTION "BeatSaver API Wrapper for C++")

if(BUILD_TEST)
find_package(Catch2 REQUIRED)
endif(BUILD_TEST)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(CURL REQUIRED)

include(GNUInstallDirs)
if(BEATCPPVER_STATIC)
	add_library(beatcppver STATIC ${BEATCPPVER_SOURCE_FILES} ${BEATCPPVER_HEADER_FILES})
	message("Building static lib")
else(BEATCPPVER_STATIC)
	add_library(beatcppver SHARED ${BEATCPPVER_SOURCE_FILES} ${BEATCPPVER_HEADER_FILES} )
	message("Building shared lib")
endif(BEATCPPVER_STATIC)
if(BUILD_TEST)
	add_executable(tst_beatcppver "${CMAKE_CURRENT_SOURCE_DIR}/test/tst_bs.cpp" ${BEATCPPVER_SOURCE_FILES})
endif(BUILD_TEST)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/beatcppver.pc.in" "${CMAKE_CURRENT_SOURCE_DIR}/beatcppver.pc" @ONLY)

include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LIBRARIES})

set_target_properties(beatcppver PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(beatcppver PROPERTIES SOVERSION 0)

set_target_properties(beatcppver PROPERTIES PUBLIC_HEADER "${BEATCPPVER_HEADER_FILES}")
target_link_libraries(beatcppver PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(beatcppver PRIVATE CURL::libcurl)
target_include_directories(beatcppver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(BUILD_TEST)
target_include_directories(tst_beatcppver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(tst_beatcppver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test)
endif(BUILD_TEST)

install(TARGETS beatcppver LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/beatcppver.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
