# - Try to find screen_capture_lite
# Once done, this will define
#
#  screen_capture_light_FOUND - system has screen_capture_lite
#  screen_capture_lite_INCLUDE_DIRS - the screen_capture_lite include directories
#  screen_capture_lite_LIBRARIES - link these to use screen_capture_lite

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(screen_capture_lite_PKGCONF screen_capture_lite)

set(INCLUDE_SEARCH_PATHS ${screen_capture_lite_PKGCONF_INCLUDE_DIRS})
if(MSVC)
	set(INCLUDE_SEARCH_PATHS "${INCLUDE_SEARCH_PATHS} 'C:/Program Files/screen_capture_lite/include'")
endif()
# Include dir
find_path(screen_capture_lite_INCLUDE_DIR
  NAMES ScreenCapture.h
  PATHS ${INCLUDE_SEARCH_PATHS}
)

set(LIBRARY_SEARCH_PATHS ${screen_capture_lite_PKGCONF_LIBRARY_DIRS})
if(MSVC)
	set(LIBRARY_SEARCH_PATHS "${INCLUDE_SEARCH_PATHS} 'C:/Program Files/screen_capture_lite/include/lib'")
endif()
# Finally the library itself
find_library(screen_capture_lite_LIBRARY
  NAMES screen_capture_lite
  PATHS ${LIBRARY_SEARCH_PATHS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(screen_capture_lite_PROCESS_INCLUDES screen_capture_lite_INCLUDE_DIR)
set(screen_capture_lite_PROCESS_LIBS screen_capture_lite_LIBRARY)

libfind_process(screen_capture_lite)