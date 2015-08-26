###################
# CMake settings. #
###################
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
SET( CMAKE_VERBOSE_MAKEFILE ON )
SET( CMAKE_COLOR_MAKEFILE ON )

#####################
# Project settings. #
#####################
PROJECT( module )

OPTION( BGE_DEBUG "Build BGE in debug mode" ON )

include_directories( ../../../../BoxE/core/ ../../../../BackGenEngine/engine/ )
#ET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Check debug mode.
IF( BGE_DEBUG )
    SET( CFLAGS ${CFLAGS} " -W -Wall -ansi -pedantic -O0 -g" )
ELSE( BGE_DEBUG )
    SET( CFLAGS ${CFLAGS} " -W -Wall -ansi -pedantic" )
ENDIF( BGE_DEBUG )


####################
# Set sourcefiles. #
####################
file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)


SET_PROPERTY( SOURCE ${SRCS} APPEND PROPERTY COMPILE_FLAGS ${CFLAGS} )

ADD_LIBRARY( BTextureAsset SHARED ${SRCS} )
TARGET_LINK_LIBRARIES( BTextureAsset ${LIBS} )
