set (CXX_SRC_FILES
    main.cpp
    elf_file.cpp
    # util
    util/binary.cpp
    # partition
    partition/identification.cpp
    partition/header.cpp
)

# Convert to absolute paths
list(TRANSFORM CXX_SRC_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(CXX_SRC_FILES ${CXX_SRC_FILES} PARENT_SCOPE)