#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "iceoryx_posh::iceoryx_posh_roudi_env" for configuration "Release"
set_property(TARGET iceoryx_posh::iceoryx_posh_roudi_env APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(iceoryx_posh::iceoryx_posh_roudi_env PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libiceoryx_posh_roudi_env.a"
  )

list(APPEND _cmake_import_check_targets iceoryx_posh::iceoryx_posh_roudi_env )
list(APPEND _cmake_import_check_files_for_iceoryx_posh::iceoryx_posh_roudi_env "${_IMPORT_PREFIX}/lib/libiceoryx_posh_roudi_env.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
