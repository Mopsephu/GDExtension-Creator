The program is free to use to create basic GDExtension project.
Source code is free to be modified and compiled on different platforms such as Windows, Linux and so on.

The program's goal is to build minimum for your GDExtension project for Godot Engine.

Structure of built GDExtension project:
1) godot-cpp
2) src:
2.1) register_types.h
2.2) register_types.cpp
3) %PROJECTNAME%:
3.1) bin:
3.1.1) %PROJECTNAME%.gdextension
3.1.2) %PROJECTNAME%.%OPERATINGSYSTEM%.template_debug
...
3.1.3+n) %PROJECTNAME%.%OPERATINGSYSTEM%.template_release
...
4) .sconsign.dblite
5) SConstruct.py

Instructions of using:
1) Start the program;
2) Read conditions closely. If they are not satisfied yet, download everything your computer does not have. After that you may use the program further;
3) State preferable version of GDExtension project, which will be suitable for version of Godot Engine:
3.1) Press Enter again;
3.2) Confirm or deny changes;
4) Type on your keyboard name of your project (%PROJECTNAME%):
4.1) Confirm or deny changes;
5) State the number of CPU cores the compiler will use to compile your project:
5.1) Confirm or deny changes;
6) Wait until the project will be fully done;
7) Success! Your project is built!