# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_BUNDLE "OFF")
set(CPACK_BINARY_DEB "OFF")
set(CPACK_BINARY_DRAGNDROP "OFF")
set(CPACK_BINARY_FREEBSD "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "OFF")
set(CPACK_BINARY_PRODUCTBUILD "OFF")
set(CPACK_BINARY_RPM "OFF")
set(CPACK_BINARY_STGZ "ON")
set(CPACK_BINARY_TBZ2 "OFF")
set(CPACK_BINARY_TGZ "ON")
set(CPACK_BINARY_TXZ "OFF")
set(CPACK_BUILD_SOURCE_DIRS "/Users/mrashcreates/Developer/safron-cli;/Users/mrashcreates/Developer/safron-cli/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_NAME "libcli11-dev")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/opt/homebrew/Cellar/cmake/3.30.4/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "SafronCLI built using CMake")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_IGNORE_FILES "/.git;/dist;/.*build.*;/\\.DS_Store;/.*\\.egg-info;/var;/azure-pipelines.yml;/.ci;/docs;/examples;/test_package;/book;/.travis.yml;.swp;/.all-contributorsrc;/.appveyor.yml;/.pre-commit.*yaml")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALLED_DIRECTORIES "/Users/mrashcreates/Developer/safron-cli;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-src/cmake")
set(CPACK_NSIS_DISPLAY_NAME "SafronCLI 2.3.2")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "SafronCLI 2.3.2")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJDUMP_EXECUTABLE "/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
set(CPACK_OSX_SYSROOT "/Applications/Xcode-beta.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.1.sdk")
set(CPACK_OUTPUT_CONFIG_FILE "/Users/mrashcreates/Developer/safron-cli/build/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "https://github.com/CLIUtils/CLI11")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-src/CLI11.CPack.Description.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Command line parser with simple and intuitive interface")
set(CPACK_PACKAGE_FILE_NAME "SafronCLI-2.3.2-Source")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "SafronCLI 2.3.2")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "SafronCLI 2.3.2")
set(CPACK_PACKAGE_NAME "SafronCLI")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "github.com/CLIUtils/CLI11")
set(CPACK_PACKAGE_VERSION "2.3.2")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "2")
set(CPACK_RESOURCE_FILE_LICENSE "/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-src/LICENSE")
set(CPACK_RESOURCE_FILE_README "/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-src/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "/opt/homebrew/Cellar/cmake/3.30.4/share/cmake/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/.git;/dist;/.*build.*;/\\.DS_Store;/.*\\.egg-info;/var;/azure-pipelines.yml;/.ci;/docs;/examples;/test_package;/book;/.travis.yml;.swp;/.all-contributorsrc;/.appveyor.yml;/.pre-commit.*yaml")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/Users/mrashcreates/Developer/safron-cli;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/Users/mrashcreates/Developer/safron-cli/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "SafronCLI-2.3.2-Source")
set(CPACK_SOURCE_TOPLEVEL_TAG "Darwin-Source")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Darwin")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Darwin-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/Users/mrashcreates/Developer/safron-cli/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
