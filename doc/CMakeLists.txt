configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

# add a target to generate API documentation with Doxygen
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(TARGET Doxygen::doxygen AND TARGET Doxygen::dot)
  add_custom_target(doc
    COMMAND Doxygen::doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
else()
  if (NOT TARGET Doxygen::doxygen)
    message(STATUS "Doxygen was not found. Documentation will not be produced. You can still produce it manually using the Doxyfile in ${CMAKE_CURRENT_BINARY_DIR}.")
  else()
    message(STATUS "dot (Graphviz utility) was not found. It is needed to render the documentation which will not be produced. You can still produce it manually using the Doxyfile in ${CMAKE_CURRENT_BINARY_DIR}.")
  endif()
endif()
