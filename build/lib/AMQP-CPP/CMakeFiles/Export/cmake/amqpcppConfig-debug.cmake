#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "amqpcpp" for configuration "Debug"
set_property(TARGET amqpcpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(amqpcpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libamqpcpp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS amqpcpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_amqpcpp "${_IMPORT_PREFIX}/lib/libamqpcpp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
