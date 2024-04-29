The program is free to use to create basic GDExtension project.
Source code is free to be modified and compiled on different platforms such as Windows, Linux and so on.

The program's goal is to build minimum for your GDExtension project for Godot Engine.

You also need to install the following software in order to make the work of the program correct:
1) Python:
1.1) Scons;
2) Git;
3) Godot Engine of version of 4.1 or above (you need it to create the project of the game engine inside of GDExtension project);
4) Good internet connection ;)

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

Explanation of the algorithm:
After user finished initial settings, program will create a folder with the stated name in stated directory and will continue working there;
Using "git clone...", the program will install repository of Godot Engine;
Program will go into 'godot-cpp' subfolder and fetches submodules via Git command;
Program will start compiling initial debug DLL, targeted on platform (Windows, Linux...) you're currently using;
After compiling of debug DLL is done, the program will do the same thing for release DLL;
After compilation is done, the program will climb up the directory, create 'src' subfolder and go into it;
There the program will create register_types.h and register_types.cpp and fill them both with basic functionality;
Next, the program will will climb up the directory again and create SConstruct.py file and fill it;
Then the program will compile the project for both debug DLL and release DLL again;
After that, the program will go into subfolder with the same name as the folder, then will go into bin folder and after that the program will create .gdextension file and fill it.
After .gdextension file is filled up, the program work is done and it will alert the user, showing in addition to that time elapsed in both seconds and minutes.

Post-work explanation:
When the work of the program is done, all you will need to do is to add new nodes in 'src' subfolder and register them properly inside of register_types.cpp.
As you will make practically not many changes in the whole project, the further compilation will be done in seconds, saving you lots of time.
Good luck in programming in GDExtension!
