set (CXX_HEADER_FILES
    elf_file.h
    # util
    util/exception.hpp
    # partitions
    partition/identification.h
)

# Convert to absolute paths
list(TRANSFORM CXX_HEADER_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(CXX_HEADER_FILES ${CXX_HEADER_FILES} PARENT_SCOPE)