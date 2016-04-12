# Usefull variables
# CMAKE_CURRENT_SOURCE_DIR = Racine du projet, dans les faits c'est le dossier ou est spécifié le CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

project(RTypeServer)
include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 --std=c++11 -pthread")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# COMPILATION DU SERVER

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/server)

file(GLOB SERVERSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Server/src/*.cpp)
file(GLOB SERVERCOMMON ${CMAKE_CURRENT_SOURCE_DIR}/Common/src/*.cpp)

MESSAGE("${SERVERSOURCES}")
MESSAGE("${SERVERCOMMON}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Server/includes")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Common/inc")

add_executable(RTypeServer ${SERVERSOURCES} ${SERVERCOMMON})

# SFML CONFIG

if (WIN32)
set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

if(WIN32)
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/SFML-2.3.2-win")
find_package(SFML 2.3.2 REQUIRED system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(RTypeServer ${SFML_LIBRARIES})

    target_link_libraries(RTypeServer 
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/flac.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/freetype.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/jpeg.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/ogg.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/openal32.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/vorbis.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/vorbisenc.lib
    					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/vorbisfile.lib
					${PROJECT_SOURCE_DIR}/SFML-2.3.2-win/lib/openal32.lib
    					winmm.lib
    					opengl32.lib	
    						)

endif(SFML_FOUND)
endif(WIN32)

if (UNIX)

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.3.2-uni")
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/SFML-2.3.2-uni")
MESSAGE(STATUS "SFML_ROOT : " ${SFML_ROOT})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.3.2-uni/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(RTypeServer ${SFML_LIBRARIES})
endif(SFML_FOUND)
  
endif(UNIX)

# END SFML CONFIG
