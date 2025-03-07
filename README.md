# make2cmake

This script can be used to generate proper CMakelist files for any make-based project.
Puthon 2.7 required.

How to use it:
1) create folder my_lib,
2) copy folder with project to build there - target_lib_src_tree,
3) create folder CMake there,
4) copy file generate_cmakelists.py to CMake folder
5) put files stdwx.c, stdwx.h, CMakeLists.txt in root folder - my_lib

ie content of my_lib befor building:
.
..
build
CMake
../generate_cmakelists.py
CMakeLists.txt
target_lib_src_tree
stdwx.c
stdwx.h

6) in CMakeLists.txt put in TARGET_LIST single target - target_lib_src_tree.
or, you can specify sub-projects by list of all sub-folders within target_lib_src_tree, 
that should be treated as a separate sub-project.
7) run cmake from build folder.
8) After that you have to edit file target_lib_src_tree/CMakelist. to exclude some files\folders

NOTE: before generaing of CMakeLists you may want to edit generate_cmakelists.py in order to define: 
src_suffix - list of file extensions to be added to SRC_* variable
inc_suffix - list of file extensions to be added to include path for compilation
main_file_names - list of file name to be treated as a executable goal (otherwise it will generate shared\static library)
exclude_dir - list of folder to be ignored during analysis (for example - build, CMakeFiles)
