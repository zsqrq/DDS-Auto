#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "iceoryx_dust::iceoryx_dust" for configuration "Release"
set_property(TARGET iceoryx_dust::iceoryx_dust APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(iceoryx_dust::iceoryx_dust PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libiceoryx_dust.so.2.90.0"
  IMPORTED_SONAME_RELEASE "libiceoryx_dust.so.2"
  )

list(APPEND _cmake_import_check_targets iceoryx_dust::iceoryx_dust )
list(APPEND _cmake_import_check_files_for_iceoryx_dust::iceoryx_dust "${_IMPORT_PREFIX}/lib/libiceoryx_dust.so.2.90.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
