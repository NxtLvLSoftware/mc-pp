# cmake_modules configuration file for the mc++ bin-util component
#
# This provides the mcpp::binutil target, which you can depend on by adding it
# to your target_link_libraries().
#
# It also defines the following variables, although using these directly is not
# necessary if you use the binutil target instead.
#  MCPP_BINUTIL_INCLUDE_DIRS
#  MCPP_BINUTIL_LIBRARIES

@PACKAGE_INIT@

include(CMakeFindDependencyMacro)

set_and_check(MCPP_INCLUDE_DIR "@PACKAGE_INCLUDE_INSTALL_DIR@")
set_and_check(MCPP_CMAKE_DIR "@PACKAGE_NETWORK_CMAKE_INSTALL_DIR@")

# find_dependency() ends up changing PACKAGE_PREFIX_DIR, so save
# mcpp::binutil's prefix directory in the MCPP_BINUTIL_PREFIX_DIR variable
set(MCPP_BINUTIL_PREFIX_DIR "${PACKAGE_PREFIX_DIR}")

# Include the mcpp-binutil-config-version.cmake & mcpp-binutil-config-targets.cmake
# files, which are generated from our cmake_modules rules
if (NOT TARGET mcpp::binutil)
  include("${MCPP_CMAKE_DIR}/mcpp-binutil-config-version.cmake")
  include("${MCPP_CMAKE_DIR}/mcpp-binutil-config-targets.cmake")
endif()

# Set MCPP_BINUTIL_LIBRARIES to the binutil target
set(MCPP_BINUTIL_LIBRARIES mcpp::binutil)

# Append the mcpp::binutil target to MCPP_LIBRARIES
set(MCPP_LIBRARIES "${MCPP_BINUTIL_LIBRARIES}")

if (NOT mcpp_binutil_FIND_QUIETLY)
  message(STATUS "Found mcpp::binutil: ${MCPP_BINUTIL_PREFIX_DIR}")
endif()