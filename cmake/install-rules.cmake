include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package super_mario_bros)

install(
    TARGETS super_mario_bros_exe
    RUNTIME COMPONENT super_mario_bros_Runtime
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    super_mario_bros_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(super_mario_bros_INSTALL_CMAKEDIR)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${super_mario_bros_INSTALL_CMAKEDIR}"
    COMPONENT super_mario_bros_Development
)

# Export variables for the install script to use
install(CODE "
set(super_mario_bros_NAME [[$<TARGET_FILE_NAME:super_mario_bros_exe>]])
set(super_mario_bros_INSTALL_CMAKEDIR [[${super_mario_bros_INSTALL_CMAKEDIR}]])
set(CMAKE_INSTALL_BINDIR [[${CMAKE_INSTALL_BINDIR}]])
" COMPONENT super_mario_bros_Development)

install(
    SCRIPT cmake/install-script.cmake
    COMPONENT super_mario_bros_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
