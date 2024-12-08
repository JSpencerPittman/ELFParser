set (CXX_SRC_FILES
    main.cpp
    elf_file.cpp
)

# Convert to absolute paths
list(TRANSFORM CXX_SRC_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

set(CXX_SRC_FILES ${CXX_SRC_FILES} PARENT_SCOPE)