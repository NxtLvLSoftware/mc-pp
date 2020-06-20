# cmake_modules configuration file for mc++ libraries.
#
# This provides the mc++ component targets, which you can depend on by adding it
# to your target_link_libraries().
#

get_filename_component(_MCPP_CMAKEDIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)
foreach(COMPONENT ${mcpp_FIND_COMPONENTS})
  include("${_MCPP_CMAKEDIR}/mcpp_${COMPONENT}-${VERSION}/mcpp-${COMPONENT}-config.cmake")
endforeach()