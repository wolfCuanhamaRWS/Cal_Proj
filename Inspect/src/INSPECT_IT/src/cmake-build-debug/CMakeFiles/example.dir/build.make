# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example.dir/flags.make

CMakeFiles/example.dir/main.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/main.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/main.cpp

CMakeFiles/example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/main.cpp > CMakeFiles/example.dir/main.cpp.i

CMakeFiles/example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/main.cpp -o CMakeFiles/example.dir/main.cpp.s

CMakeFiles/example.dir/lib/connection.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/lib/connection.cpp.o: ../lib/connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/example.dir/lib/connection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/lib/connection.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/lib/connection.cpp

CMakeFiles/example.dir/lib/connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/lib/connection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/lib/connection.cpp > CMakeFiles/example.dir/lib/connection.cpp.i

CMakeFiles/example.dir/lib/connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/lib/connection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/lib/connection.cpp -o CMakeFiles/example.dir/lib/connection.cpp.s

CMakeFiles/example.dir/lib/graphviewer.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/lib/graphviewer.cpp.o: ../lib/graphviewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/example.dir/lib/graphviewer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/lib/graphviewer.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/lib/graphviewer.cpp

CMakeFiles/example.dir/lib/graphviewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/lib/graphviewer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/lib/graphviewer.cpp > CMakeFiles/example.dir/lib/graphviewer.cpp.i

CMakeFiles/example.dir/lib/graphviewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/lib/graphviewer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/lib/graphviewer.cpp -o CMakeFiles/example.dir/lib/graphviewer.cpp.s

CMakeFiles/example.dir/resources/Data.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/Data.cpp.o: ../resources/Data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/example.dir/resources/Data.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/Data.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Data.cpp

CMakeFiles/example.dir/resources/Data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/Data.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Data.cpp > CMakeFiles/example.dir/resources/Data.cpp.i

CMakeFiles/example.dir/resources/Data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/Data.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Data.cpp -o CMakeFiles/example.dir/resources/Data.cpp.s

CMakeFiles/example.dir/resources/AgenteEconomico.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/AgenteEconomico.cpp.o: ../resources/AgenteEconomico.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/example.dir/resources/AgenteEconomico.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/AgenteEconomico.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/AgenteEconomico.cpp

CMakeFiles/example.dir/resources/AgenteEconomico.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/AgenteEconomico.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/AgenteEconomico.cpp > CMakeFiles/example.dir/resources/AgenteEconomico.cpp.i

CMakeFiles/example.dir/resources/AgenteEconomico.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/AgenteEconomico.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/AgenteEconomico.cpp -o CMakeFiles/example.dir/resources/AgenteEconomico.cpp.s

CMakeFiles/example.dir/resources/menus.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/menus.cpp.o: ../resources/menus.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/example.dir/resources/menus.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/menus.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/menus.cpp

CMakeFiles/example.dir/resources/menus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/menus.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/menus.cpp > CMakeFiles/example.dir/resources/menus.cpp.i

CMakeFiles/example.dir/resources/menus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/menus.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/menus.cpp -o CMakeFiles/example.dir/resources/menus.cpp.s

CMakeFiles/example.dir/resources/utils.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/utils.cpp.o: ../resources/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/example.dir/resources/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/utils.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/utils.cpp

CMakeFiles/example.dir/resources/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/utils.cpp > CMakeFiles/example.dir/resources/utils.cpp.i

CMakeFiles/example.dir/resources/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/utils.cpp -o CMakeFiles/example.dir/resources/utils.cpp.s

CMakeFiles/example.dir/resources/Brigada.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/Brigada.cpp.o: ../resources/Brigada.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/example.dir/resources/Brigada.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/Brigada.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Brigada.cpp

CMakeFiles/example.dir/resources/Brigada.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/Brigada.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Brigada.cpp > CMakeFiles/example.dir/resources/Brigada.cpp.i

CMakeFiles/example.dir/resources/Brigada.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/Brigada.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Brigada.cpp -o CMakeFiles/example.dir/resources/Brigada.cpp.s

CMakeFiles/example.dir/resources/Local.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/Local.cpp.o: ../resources/Local.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/example.dir/resources/Local.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/Local.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Local.cpp

CMakeFiles/example.dir/resources/Local.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/Local.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Local.cpp > CMakeFiles/example.dir/resources/Local.cpp.i

CMakeFiles/example.dir/resources/Local.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/Local.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Local.cpp -o CMakeFiles/example.dir/resources/Local.cpp.s

CMakeFiles/example.dir/resources/MapImport.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/MapImport.cpp.o: ../resources/MapImport.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/example.dir/resources/MapImport.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/MapImport.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/MapImport.cpp

CMakeFiles/example.dir/resources/MapImport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/MapImport.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/MapImport.cpp > CMakeFiles/example.dir/resources/MapImport.cpp.i

CMakeFiles/example.dir/resources/MapImport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/MapImport.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/MapImport.cpp -o CMakeFiles/example.dir/resources/MapImport.cpp.s

CMakeFiles/example.dir/resources/AutoridadePublica.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/AutoridadePublica.cpp.o: ../resources/AutoridadePublica.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/example.dir/resources/AutoridadePublica.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/AutoridadePublica.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/AutoridadePublica.cpp

CMakeFiles/example.dir/resources/AutoridadePublica.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/AutoridadePublica.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/AutoridadePublica.cpp > CMakeFiles/example.dir/resources/AutoridadePublica.cpp.i

CMakeFiles/example.dir/resources/AutoridadePublica.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/AutoridadePublica.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/AutoridadePublica.cpp -o CMakeFiles/example.dir/resources/AutoridadePublica.cpp.s

CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.o: ../resources/HeuristicsFindRoute.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/HeuristicsFindRoute.cpp

CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/HeuristicsFindRoute.cpp > CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.i

CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/HeuristicsFindRoute.cpp -o CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.s

CMakeFiles/example.dir/resources/RouteViewCalc.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/RouteViewCalc.cpp.o: ../resources/RouteViewCalc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/example.dir/resources/RouteViewCalc.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/RouteViewCalc.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/RouteViewCalc.cpp

CMakeFiles/example.dir/resources/RouteViewCalc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/RouteViewCalc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/RouteViewCalc.cpp > CMakeFiles/example.dir/resources/RouteViewCalc.cpp.i

CMakeFiles/example.dir/resources/RouteViewCalc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/RouteViewCalc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/RouteViewCalc.cpp -o CMakeFiles/example.dir/resources/RouteViewCalc.cpp.s

CMakeFiles/example.dir/resources/Conectividade.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/resources/Conectividade.cpp.o: ../resources/Conectividade.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/example.dir/resources/Conectividade.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/resources/Conectividade.cpp.o -c /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Conectividade.cpp

CMakeFiles/example.dir/resources/Conectividade.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/resources/Conectividade.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Conectividade.cpp > CMakeFiles/example.dir/resources/Conectividade.cpp.i

CMakeFiles/example.dir/resources/Conectividade.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/resources/Conectividade.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/resources/Conectividade.cpp -o CMakeFiles/example.dir/resources/Conectividade.cpp.s

# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/main.cpp.o" \
"CMakeFiles/example.dir/lib/connection.cpp.o" \
"CMakeFiles/example.dir/lib/graphviewer.cpp.o" \
"CMakeFiles/example.dir/resources/Data.cpp.o" \
"CMakeFiles/example.dir/resources/AgenteEconomico.cpp.o" \
"CMakeFiles/example.dir/resources/menus.cpp.o" \
"CMakeFiles/example.dir/resources/utils.cpp.o" \
"CMakeFiles/example.dir/resources/Brigada.cpp.o" \
"CMakeFiles/example.dir/resources/Local.cpp.o" \
"CMakeFiles/example.dir/resources/MapImport.cpp.o" \
"CMakeFiles/example.dir/resources/AutoridadePublica.cpp.o" \
"CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.o" \
"CMakeFiles/example.dir/resources/RouteViewCalc.cpp.o" \
"CMakeFiles/example.dir/resources/Conectividade.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

example: CMakeFiles/example.dir/main.cpp.o
example: CMakeFiles/example.dir/lib/connection.cpp.o
example: CMakeFiles/example.dir/lib/graphviewer.cpp.o
example: CMakeFiles/example.dir/resources/Data.cpp.o
example: CMakeFiles/example.dir/resources/AgenteEconomico.cpp.o
example: CMakeFiles/example.dir/resources/menus.cpp.o
example: CMakeFiles/example.dir/resources/utils.cpp.o
example: CMakeFiles/example.dir/resources/Brigada.cpp.o
example: CMakeFiles/example.dir/resources/Local.cpp.o
example: CMakeFiles/example.dir/resources/MapImport.cpp.o
example: CMakeFiles/example.dir/resources/AutoridadePublica.cpp.o
example: CMakeFiles/example.dir/resources/HeuristicsFindRoute.cpp.o
example: CMakeFiles/example.dir/resources/RouteViewCalc.cpp.o
example: CMakeFiles/example.dir/resources/Conectividade.cpp.o
example: CMakeFiles/example.dir/build.make
example: CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example.dir/build: example

.PHONY : CMakeFiles/example.dir/build

CMakeFiles/example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example.dir/clean

CMakeFiles/example.dir/depend:
	cd /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug /home/flavio/CAL/Cal_Proj/Inspect/src/INSPECT_IT/src/cmake-build-debug/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example.dir/depend
