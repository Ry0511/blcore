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
# | BLCORE |
################################################################################

set(BLCORE_FLAVOUR "" CACHE STRING "Which game to build for: WILLOW (BL1) or WILLOW64 (BL1E), set by the presets")
set_property(CACHE BLCORE_FLAVOUR PROPERTY STRINGS "WILLOW" "WILLOW64")
if (NOT BLCORE_FLAVOUR MATCHES "^(WILLOW|WILLOW64)$")
  message(FATAL_ERROR "Got invalid blcore flavour '${BLCORE_FLAVOUR}', configure with one of the presets")
endif ()

set(CONFIGURE_FILES_DIR "${CMAKE_CURRENT_BINARY_DIR}/configure")
set(GIT_HEAD_SHA1 "@GIT_HEAD_SHA1@")
configure_file(
    "src/blcore/version.inl.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.inl.in"
    @ONLY
)
unset(GIT_HEAD_SHA1)

set(GIT_PRE_CONFIGURE_FILE "${CMAKE_CURRENT_BINARY_DIR}/version.inl.in")
set(GIT_POST_CONFIGURE_FILE "${CONFIGURE_FILES_DIR}/blcore/version.inl")
include(cmake/git_watcher.cmake)

file(GLOB_RECURSE BLCORE_SOURCE_LIST CONFIGURE_DEPENDS src/blcore/*.cpp src/blcore/*.h)
list(APPEND BLCORE_SOURCE_LIST ${GIT_POST_CONFIGURE_FILE})

add_library(blcore SHARED ${BLCORE_SOURCE_LIST} src/blcore/version.rc)
add_library(blcore::blcore ALIAS blcore)

target_include_directories(blcore PUBLIC src ${CONFIGURE_FILES_DIR})
target_compile_features(blcore PUBLIC cxx_std_23)
target_compile_definitions(
    blcore
    PUBLIC
    ${BLCORE_FLAVOUR}
    PRIVATE
    BLCORE_EXPORTS
)
target_link_libraries(blcore PRIVATE minhook PUBLIC libhat::libhat)

if (MSVC)
  target_compile_options(blcore PRIVATE /W4 /EHsc /utf-8)
endif ()

install(TARGETS blcore RUNTIME DESTINATION .)

if (MSVC)
  install(FILES $<TARGET_PDB_FILE:blcore> DESTINATION . OPTIONAL)
endif ()

add_subdirectory(test)
