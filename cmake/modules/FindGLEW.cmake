# - Try to find GLEW
# Once done this will define
#  
#  GLEW_FOUND        - system has GLEW
#  GLEW_INCLUDE_DIR  - the GL include directory
#  GLEW_LIBRARIES    - Link these to use GLEW
#   
# On OSX default to using the framework version of glew
# People will have to change the cache values of GLEW_LIBRARY 
# to use GLEW with X11 on OSX

#=============================================================================
# Copyright 2001-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

IF (WIN32)
    FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h )
    FIND_LIBRARY(GLEW_LIBRARY NAMES glew glew32 )
ELSE (WIN32)

  IF (APPLE)

    FIND_LIBRARY(GLEW_LIBRARY GLEW DOC "GLEW lib for OSX")
    FIND_PATH(GLEW_INCLUDE_DIR OpenGL/glew.h DOC "Include for GLEW on OSX")

  ELSE(APPLE)
    # Handle HP-UX cases where we only want to find OpenGL in either hpux64
    # or hpux32 depending on if we're doing a 64 bit build.
    IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
      SET(HPUX_IA_GLEW_LIB_PATH /opt/graphics/OpenGL/lib/hpux32/)
    ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
      SET(HPUX_IA_GLEW_LIB_PATH 
        /opt/graphics/OpenGL/lib/hpux64/
        /opt/graphics/OpenGL/lib/pa20_64)
    ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

    # The first line below is to make sure that the proper headers
    # are used on a Linux machine with the NVidia drivers installed.
    # They replace Mesa with NVidia's own library but normally do not
    # install headers and that causes the linking to
    # fail since the compiler finds the Mesa headers but NVidia's library.
    # Make sure the NVIDIA directory comes BEFORE the others.
    #  - Atanas Georgiev <atanas@cs.columbia.edu>

    FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h
      /usr/share/doc/NVIDIA_GLX-1.0/include
      /usr/openwin/share/include
      /opt/graphics/OpenGL/include /usr/X11R6/include
    )

    FIND_LIBRARY(GLEW_LIBRARY
      NAMES GLEW
      PATHS /opt/graphics/OpenGL/lib
            /usr/openwin/lib
            /usr/shlib /usr/X11R6/lib
            ${HPUX_IA_GLEW_LIB_PATH}
    )

  ENDIF(APPLE)
ENDIF (WIN32)

# handle the QUIETLY and REQUIRED arguments and set GLEW_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW REQUIRED_VARS GLEW_LIBRARY GLEW_INCLUDE_DIR)

IF(GLEW_FOUND)

    SET( GLEW_LIBRARIES  ${GLEW_LIBRARY} ${GLEW_LIBRARIES})

ENDIF(GLEW_FOUND)

MARK_AS_ADVANCED(
  GLEW_INCLUDE_DIR
)
