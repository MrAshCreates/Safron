# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild

# Utility rule file for cli11-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/cli11-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cli11-populate.dir/progress.make

CMakeFiles/cli11-populate: CMakeFiles/cli11-populate-complete

CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-install
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-mkdir
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-download
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-configure
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-build
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-install
CMakeFiles/cli11-populate-complete: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'cli11-populate'"
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E make_directory /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles/cli11-populate-complete
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-done

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update:
.PHONY : cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-build: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'cli11-populate'"
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E echo_append
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-build

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-configure: cli11-populate-prefix/tmp/cli11-populate-cfgcmd.txt
cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-configure: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'cli11-populate'"
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E echo_append
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-configure

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-download: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-gitinfo.txt
cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-download: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'cli11-populate'"
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/tmp/cli11-populate-gitclone.cmake
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-download

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-install: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'cli11-populate'"
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E echo_append
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-install

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'cli11-populate'"
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -Dcfgdir= -P /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/tmp/cli11-populate-mkdirs.cmake
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-mkdir

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch-info.txt
cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'cli11-populate'"
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E echo_append
	/opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update:
.PHONY : cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-test: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'cli11-populate'"
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E echo_append
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-build && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E touch /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-test

cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update: cli11-populate-prefix/tmp/cli11-populate-gitupdate.cmake
cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update-info.txt
cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'cli11-populate'"
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-src && /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -Dcan_fetch=YES -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/cli11-populate-prefix/tmp/cli11-populate-gitupdate.cmake

cli11-populate: CMakeFiles/cli11-populate
cli11-populate: CMakeFiles/cli11-populate-complete
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-build
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-configure
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-download
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-install
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-mkdir
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-patch
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-test
cli11-populate: cli11-populate-prefix/src/cli11-populate-stamp/cli11-populate-update
cli11-populate: CMakeFiles/cli11-populate.dir/build.make
.PHONY : cli11-populate

# Rule to build all files generated by this target.
CMakeFiles/cli11-populate.dir/build: cli11-populate
.PHONY : CMakeFiles/cli11-populate.dir/build

CMakeFiles/cli11-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cli11-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cli11-populate.dir/clean

CMakeFiles/cli11-populate.dir/depend:
	cd /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild /Users/mrashcreates/Developer/safron-cli/build/_deps/cli11-subbuild/CMakeFiles/cli11-populate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cli11-populate.dir/depend
