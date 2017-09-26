#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Tasks::Tasks" for configuration "Release"
set_property(TARGET Tasks::Tasks APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Tasks::Tasks PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "/usr/lib/x86_64-linux-gnu/libboost_timer.so;/usr/lib/x86_64-linux-gnu/libboost_chrono.so;/usr/lib/x86_64-linux-gnu/libboost_system.so"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libTasks.so.0.9.0"
  IMPORTED_SONAME_RELEASE "libTasks.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS Tasks::Tasks )
list(APPEND _IMPORT_CHECK_FILES_FOR_Tasks::Tasks "${_IMPORT_PREFIX}/lib/libTasks.so.0.9.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
