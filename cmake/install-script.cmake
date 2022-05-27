file(
    RELATIVE_PATH relative_path
    "/${super_mario_bros_INSTALL_CMAKEDIR}"
    "/${CMAKE_INSTALL_BINDIR}/${super_mario_bros_NAME}"
)

get_filename_component(prefix "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)
set(config_dir "${prefix}/${super_mario_bros_INSTALL_CMAKEDIR}")
set(config_file "${config_dir}/super_mario_brosConfig.cmake")

message(STATUS "Installing: ${config_file}")
file(WRITE "${config_file}" "\
get_filename_component(
    _super_mario_bros_executable
    \"\${CMAKE_CURRENT_LIST_DIR}/${relative_path}\"
    ABSOLUTE
)
set(
    SUPER_MARIO_BROS_EXECUTABLE \"\${_super_mario_bros_executable}\"
    CACHE FILEPATH \"Path to the super_mario_bros executable\"
)
")
list(APPEND CMAKE_INSTALL_MANIFEST_FILES "${config_file}")
