# Usefull variables
# CMAKE_CURRENT_SOURCE_DIR = Dossier actuel, dans les faits c'est le dossier ou est spécifié le CMakeLists.txt top level

cmake_minimum_required(VERSION 3.0)

project(RTypeClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 --std=c++11")
# COMPILATION DU CLIENT

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/client)

file(GLOB CLIENTSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Client/src/*.cpp)
file(GLOB CLIENTCOMMON ${CMAKE_CURRENT_SOURCE_DIR}/Common/src/*.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Client/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Client/inc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Common/inc")

add_executable(RTypeClient ${CLIENTSOURCES} ${CLIENTCOMMON})

# SFML CONFIG

if (WIN32)
set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

if(WIN32)
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/SFML-2.3.2-win")
find_package(SFML 2.3.2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(RTypeClient ${SFML_LIBRARIES})

    target_link_libraries(RTypeClient 
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
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(RTypeClient ${SFML_LIBRARIES})
endif(SFML_FOUND)
  
endif(UNIX)

# END SFML CONFIG
