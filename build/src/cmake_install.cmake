# Install script for directory: /home/icubuser/mc/install/Tasks/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTasks.so.0.9.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTasks.so.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTasks.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/icubuser/mc/install/Tasks/build/src/libTasks.so.0.9.0"
    "/home/icubuser/mc/install/Tasks/build/src/libTasks.so.0"
    "/home/icubuser/mc/install/Tasks/build/src/libTasks.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTasks.so.0.9.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTasks.so.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTasks.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Tasks" TYPE FILE FILES
    "/home/icubuser/mc/install/Tasks/src/Tasks.h"
    "/home/icubuser/mc/install/Tasks/src/QPSolver.h"
    "/home/icubuser/mc/install/Tasks/src/QPTasks.h"
    "/home/icubuser/mc/install/Tasks/src/QPConstr.h"
    "/home/icubuser/mc/install/Tasks/src/QPContacts.h"
    "/home/icubuser/mc/install/Tasks/src/QPSolverData.h"
    "/home/icubuser/mc/install/Tasks/src/QPMotionConstr.h"
    "/home/icubuser/mc/install/Tasks/src/GenQPSolver.h"
    "/home/icubuser/mc/install/Tasks/src/Bounds.h"
    "/home/icubuser/mc/install/Tasks/src/QPContactConstr.h"
    "/home/icubuser/mc/install/Tasks/src/QLDQPSolver.h"
    "/home/icubuser/mc/install/Tasks/src/LSSOLQPSolver.h"
    )
endif()

