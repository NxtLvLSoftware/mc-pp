set(EXAMPLE varints)
set(TARGET ${COMPONENT}_${EXAMPLE}_example)

# Create the executable target & namespaced alias
add_executable(${TARGET} varints.cpp)

target_link_libraries(${TARGET}
  PUBLIC
  mcpp::binutil
)