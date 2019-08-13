# Get needed dependencies
find_package(Doxygen REQUIRED)

# Get all public headers
get_target_property(LIBRG_CPP_PUBLIC_HEADER_DIRS librg_cpp INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE LIBRG_CPP_PUBLIC_HEADER_DIRS ${LIBRG_CPP_PUBLIC_HEADER_DIRS}/*.h)

set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/include)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/docs/)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)

set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

# Generate doxygen config file
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${LIBRG_CPP_PUBLIC_HEADER_DIRS}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
