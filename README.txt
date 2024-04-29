EN (English):
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



RU (Русский):
Программу можно бесплатно использовать для создания базового проекта GDExtension.
Исходный код может быть свободно изменен и скомпилирован на различных платформах, таких как Windows, Linux и так далее.

Цель программы - создать минимум для вашего проекта GDExtension для движка Godot Engine.

Для корректной работы программы Вам также необходимо установить следующее программное обеспечение:
1) Python:
1.1) Scons;
2) Git;
3) Godot Engine версии 4.1 или выше (он нужен для создания проекта игрового движка внутри проекта GDExtension);
4) Хорошее подключение к Интернету ;)

Structure of built GDExtension project:
1) godot-cpp
2) src:
2.1) register_types.h
2.2) register_types.cpp
3) %ИМЯПРОЕКТА%:
3.1) bin:
3.1.1) %ИМЯПРОЕКТА%.gdextension
3.1.2) %ИМЯПРОЕКТА%.%ОПЕРАЦИОННАЯСИСТЕМА%.template_debug
...
3.1.3+n) %ИМЯПРОЕКТА%.%ОПЕРАЦИОННАЯСИСТЕМА%.template_release
...
4) .sconsign.dblite
5) SConstruct.py

Объяснение алгоритма:
После того, как пользователь выполнит первоначальные настройки, программа создаст папку с указанным именем в указанном каталоге и продолжит работу там;
Используя "git clone...", программа установит репозиторий движка Godot;
Программа перейдет в подпапку "godot-cpp" и выберет подмодули с помощью команды Git;
Программа начнет компиляцию начальной отладочной библиотеки DLL, ориентированной на платформу (Windows, Linux...), которую вы используете в данный момент;
После завершения компиляции debug DLL программа проделает то же самое с release DLL;
После завершения компиляции программа поднимется по каталогу, создаст подпапку "src" и перейдет в нее;
Там программа создаст register_types.h и register_types.cpp и наполнит их оба базовым функционалом.
Затем программа снова поднимется по каталогу и создаст SConstruct.py файл и заполнит его;
Затем программа снова скомпилирует проект как для debug DLL, так и для release DLL;
После этого программа перейдет в подпапку с тем же именем, что и у папки, затем перейдет в папку bin, после чего программа создаст файл .gdextension и заполнит его.
После того, как файл .gdextension будет заполнен, работа программы будет завершена, и она предупредит пользователя, указав в дополнение к этому прошедшее время как в секундах, так и в минутах.

Пояснение после работы:
Когда работа программы будет завершена, всё, что Вам нужно будет сделать, это добавить новые ноды в подпапку 'src' и должным образом зарегистрировать их внутри register_types.cpp.
Поскольку Вы внесёте практически мало изменений во весь проект, дальнейшая компиляция будет выполнена за считанные секунды, что сэкономит вам массу времени.
Удачи в программировании в GDExtension!
