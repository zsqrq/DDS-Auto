#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "iceoryx_binding_c::iceoryx_binding_c" for configuration "Release"
set_property(TARGET iceoryx_binding_c::iceoryx_binding_c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(iceoryx_binding_c::iceoryx_binding_c PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "iceoryx_posh::iceoryx_posh"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libiceoryx_binding_c.so.2.90.0"
  IMPORTED_SONAME_RELEASE "libiceoryx_binding_c.so.2"
  )

list(APPEND _cmake_import_check_targets iceoryx_binding_c::iceoryx_binding_c )
list(APPEND _cmake_import_check_files_for_iceoryx_binding_c::iceoryx_binding_c "${_IMPORT_PREFIX}/lib/libiceoryx_binding_c.so.2.90.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
