cmake_minimum_required(VERSION 4.0)
project(
    blcore
    VERSION 0.0.0
    LANGUAGES CXX C
)

################################################################################
# | DEPENDENCIES |
################################################################################

include(FetchContent)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG v1.3.4
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL
)
set(CMAKE_SKIP_INSTALL_RULES ON)
FetchContent_MakeAvailable(minhook)
set(CMAKE_SKIP_INSTALL_RULES OFF)

set(LIBHAT_INSTALL_TARGET OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG v0.11.1
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(libhat)

################################################################################
# | CONFIGURATION |
################################################################################

# stolen from unrealsdk though we only care about BL1 and BL1E
set(BLCORE_FLAVOUR "" CACHE STRING "")
set_property(CACHE BLCORE_FLAVOUR PROPERTY STRINGS "WILLOW" "WILLOW64")
if (NOT BLCORE_FLAVOUR MATCHES "^(WILLOW|WILLOW64)$")
  message(FATAL_ERROR "invalid flavour '${BLCORE_FLAVOUR}'")
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# shared compiler settings
add_library(blcore_settings INTERFACE)
target_compile_features(blcore_settings INTERFACE cxx_std_23)
if (MSVC)
  target_compile_options(blcore_settings INTERFACE /W4 /EHsc /utf-8)
endif ()

################################################################################
# | BLCORE_COMMON |
################################################################################

file(GLOB_RECURSE BLCORE_COMMON_SOURCE_LIST CONFIGURE_DEPENDS src/common/*.cpp src/common/*.h)
file(GLOB_RECURSE BLCORE_COMMON_HEADER_LIST CONFIGURE_DEPENDS src/common/*.h)

add_library(blcore_common STATIC ${BLCORE_COMMON_SOURCE_LIST})

target_sources(blcore_common PUBLIC FILE_SET HEADERS BASE_DIRS src/common FILES ${BLCORE_COMMON_HEADER_LIST})
target_include_directories(blcore_common PUBLIC src/common)
target_compile_definitions(blcore_common PUBLIC ${BLCORE_FLAVOUR})
target_compile_features(blcore_common PUBLIC cxx_std_23)
target_link_libraries(blcore_common PRIVATE blcore_settings shell32)

################################################################################
# | BLCORE_DLL |
################################################################################

set(CONFIGURE_FILES_DIR "${CMAKE_CURRENT_BINARY_DIR}/configure")
set(GIT_HEAD_SHA1 "@GIT_HEAD_SHA1@")
configure_file(
    "src/dll/blcore/version.inl.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.inl.in"
    @ONLY
)
unset(GIT_HEAD_SHA1)

set(GIT_PRE_CONFIGURE_FILE "${CMAKE_CURRENT_BINARY_DIR}/version.inl.in")
set(GIT_POST_CONFIGURE_FILE "${CONFIGURE_FILES_DIR}/blcore/version.inl")
include(cmake/git_watcher.cmake)

file(GLOB_RECURSE BLCORE_DLL_SOURCE_LIST CONFIGURE_DEPENDS src/dll/*.cpp src/dll/*.h)
file(GLOB_RECURSE BLCORE_DLL_HEADER_LIST CONFIGURE_DEPENDS src/dll/include/*.h)
list(APPEND BLCORE_DLL_SOURCE_LIST ${GIT_POST_CONFIGURE_FILE})

add_library(blcore_dll SHARED ${BLCORE_DLL_SOURCE_LIST} src/dll/blcore/version.rc)

set_target_properties(blcore_dll
    PROPERTIES
    OUTPUT_NAME blcore
    ARCHIVE_OUTPUT_NAME blcore_dll
)

target_sources(blcore_dll PUBLIC FILE_SET HEADERS BASE_DIRS src/dll/include FILES ${BLCORE_DLL_HEADER_LIST})
target_include_directories(blcore_dll PUBLIC src/dll/include PRIVATE src/dll ${CONFIGURE_FILES_DIR})
target_compile_definitions(blcore_dll PRIVATE BLCORE_EXPORTS)
target_link_libraries(blcore_dll PUBLIC blcore_common libhat::libhat PRIVATE minhook blcore_settings)

install(TARGETS blcore_dll RUNTIME DESTINATION .)

if (MSVC)
  install(FILES $<TARGET_PDB_FILE:blcore_dll> DESTINATION . OPTIONAL)
endif ()

################################################################################
# | BLCORE |
################################################################################

file(GLOB_RECURSE BLCORE_SOURCE_LIST CONFIGURE_DEPENDS src/lib/*.cpp src/lib/*.h)
file(GLOB_RECURSE BLCORE_HEADER_LIST CONFIGURE_DEPENDS src/lib/*.h)

add_library(blcore STATIC ${BLCORE_SOURCE_LIST})
add_library(blcore::blcore ALIAS blcore)

target_sources(blcore PUBLIC FILE_SET HEADERS BASE_DIRS src/lib FILES ${BLCORE_HEADER_LIST})
target_include_directories(blcore PUBLIC src/lib)
target_link_libraries(blcore PUBLIC blcore_dll PRIVATE blcore_settings)

################################################################################
# | HEADER CHECKS |
################################################################################

option(BLCORE_HEADER_CHECKS "" ${PROJECT_IS_TOP_LEVEL})
if (BLCORE_HEADER_CHECKS)
  set_target_properties(blcore_common blcore_dll blcore PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)

  add_custom_target(blcore_header_checks ALL)
  add_dependencies(
      blcore_header_checks
      blcore_common_verify_interface_header_sets
      blcore_dll_verify_interface_header_sets
      blcore_verify_interface_header_sets
  )
endif ()

################################################################################
# | SAMPLES |
################################################################################

option(BLCORE_SAMPLES "Build the sample plugins" ${PROJECT_IS_TOP_LEVEL})
if (BLCORE_SAMPLES)
  add_subdirectory(sample)
endif ()
