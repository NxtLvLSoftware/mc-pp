# Build mc++ framework libraries
#
#

cmake_minimum_required(VERSION 3.15)

set(PROJECT mcpp)
set(VERSION "0.0.1-dev#1")
set(CMAKE_CXX_STANDARD 20)

project(mcpp)

# includes
set(CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules"
  ${CMAKE_MODULE_PATH}
)

set(INCLUDE_INSTALL_DIR include CACHE STRING
  "The subdirectory where header files should be installed")
set(LIB_INSTALL_DIR lib CACHE STRING
  "The subdirectory where libraries should be installed")
set(BIN_INSTALL_DIR bin CACHE STRING
  "The subdirectory where binaries should be installed")
set(CMAKE_INSTALL_DIR "lib/cmake/${PROJECT}" CACHE STRING
  "The subdirectory where CMake package config files should be installed")
set(MCPP_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_DIR}-${VERSION}" CACHE STRING
  "The subdirectory where CMake package config files should be installed")

#option(BUILD_STREAM "Enable building stream library." ON)
option(BUILD_BINUTIL "Enable building binutil library." ON)
option(BUILD_RAKNET "Enable building raknet library." ON)

#if(BUILD_STREAM)
#  add_subdirectory(stream)
#endif()

if(BUILD_BINUTIL)
  add_subdirectory(binutil)
endif()

if(BUILD_RAKNET)
  add_subdirectory(raknet)
endif()

# Generate the mcpp.cmake file for installation so that projects
# that use mc++ can easily depend on it in their cmake_modules
# files using "find_package(mcpp CONFIG)"
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config.cmake"
  "${MCPP_CMAKE_INSTALL_DIR}/${PROJECT}-config.cmake"
  @ONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config-version.cmake"
  VERSION ${VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config.cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config-version.cmake"
  DESTINATION ${MCPP_CMAKE_INSTALL_DIR}
)