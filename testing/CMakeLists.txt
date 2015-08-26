###################
# Cmake settings. #
###################
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
SET( CMAKE_VERBOSE_MAKEFILE ON )
SET( CMAKE_COLOR_MAKEFILE ON )

####################
# Project setting. #
####################
PROJECT( testapp )

OPTION( TESTAPP_DEBUG "Build TestApp in debug mode" ON )

# Check debug mode.
IF( TESTAPP_DEBUG )
    SET( CFLAGS ${CFLAGS} "-ansi -Wall -W -pedantic -O0 -g -DEBUG" )
ELSE( TESTAPP_DEBUG )
    SET( CFLAGS "-ansi -Wall -W -pedantic -O3 -m64"  )
ENDIF( TESTAPP_DEBUG ) 

if( ${UNIX} )
    add_definitions(-DB_OS_UNIX)
elseif( ${WIN32} )
    add_definitions(-DB_OS_WIN)
elseif( ${APPLE} )
    add_definitions(-DB_OS_APPLE)
endif()

#########################
# Find and set library. #
#########################

####################
# Set sourcefiles. #
####################
SET( SRCS ../modules/renderer/opengl/bopenglrenderer.cpp
    ../modules/renderer/opengl/bopenglframebuffer.cpp
    ../modules/renderer/opengl/bopengltexture.cpp
    ./src/bsdlwindow.cpp
    ./src/main.cpp )

SET_PROPERTY( SOURCE ${SRCS} APPEND PROPERTY COMPILE_FLAGS ${CFLAGS} )

ADD_EXECUTABLE(testapp ${SRCS})
TARGET_LINK_LIBRARIES(testapp ${LIBS} boxe-core backgenengine pthread SDL GL GLU GLEW BMeshRendererComponent BTextureAsset BMaterialAsset )