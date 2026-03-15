# Try to find Config++ (LibConfig++) on both macOS and Linux

# Include standard find package behavior
include(FindPackageHandleStandardArgs)

# Find the include directory
find_path(CONFIG++_INCLUDE_DIR
    NAMES libconfig.h++
    HINTS /usr/include /usr/local/include /opt/local/include
    PATH_SUFFIXES libconfig++
)

# Find the library
find_library(CONFIG++_LIBRARY
    NAMES config++
    HINTS /usr/lib /usr/local/lib /opt/local/lib /opt/homebrew/lib
)

# Also set the standard Config++_LIBRARIES variable for compatibility
set(Config++_LIBRARIES "${CONFIG++_LIBRARY}")

# Use find_package_handle_standard_args to handle the standard logic
find_package_handle_standard_args(Config++
    REQUIRED_VARS CONFIG++_INCLUDE_DIR CONFIG++_LIBRARY
)

if(CONFIG++_FOUND)
    # Create imported target for modern CMake usage
    if(NOT TARGET Config++::Config++)
        add_library(Config++::Config++ UNKNOWN IMPORTED)
        set_target_properties(Config++::Config++ PROPERTIES
            IMPORTED_LOCATION "${CONFIG++_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${CONFIG++_INCLUDE_DIR}"
        )
    endif()

    if(NOT CONFIG++_FIND_QUIETLY)
        message(STATUS "Found Config++: ${CONFIG++_LIBRARY}")
    endif()
else()
    if(Config++_FIND_REQUIRED)
        if(NOT CONFIG++_INCLUDE_DIR)
            message(FATAL_ERROR "Could not find LibConfig++ header file!")
        endif()
        if(NOT CONFIG++_LIBRARY)
            message(FATAL_ERROR "Could not find LibConfig++ library file!")
        endif()
    endif()
endif()
