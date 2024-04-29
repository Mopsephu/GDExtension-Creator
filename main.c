#include "main.h"

//Всё делается через указатели!
void floor_to(unsigned const short rounder, float* number)
{
    *number = floorf(*number * rounder) / rounder;
}

int is_directory_exists(const char *path)
{
    if (access(path, F_OK) == 0)
        return 1; // директория существует
    return 0; // директория не существует
}

int has_forbidden_symbols(char *folder_name)
{
    for (unsigned short i = 0; folder_name[i] != '\0'; i++)
    {
        if (folder_name[i] == '\\' || folder_name[i] == '/' || folder_name[i] == '*' || folder_name[i] == ':' || folder_name[i] == '?' || folder_name[i] == '|' || folder_name[i] == '"' || folder_name[i] == '<' || folder_name[i] == '>')
            return 1;
    }
    return 0;
}

void fprint_double_quote(FILE *file)
{
    fprintf(file, "\"");
}

void fwrap_in_double_quotes(FILE *file, char* text)
{
    fprint_double_quote(file);
    fprintf(file, text);
    fprint_double_quote(file);
}

int main(void)
{
    printf("This program will install everything to create basic GDExtension project.\nHere what you MUST have installed:\n");
    printf("\tPython => Scons (pip install scons);\n\tGodot Engine v4.1 or above;\n\tGit;\n\tGood internet connection.\n");
    
    //Спрашиваем пользователя о наличии предустановленных компонентов. Если их нет, закрыть программу
    printf("If you have them all installed, press 'y', otherwise the program will be closed: ");
    char decision = getchar();
    endl;
    if (decision != 'y')
    {
        //printf("The decision is %c", decision);
        printf("Program finished!\n");
        system("pause");
        return 0;
    }
    
    //Просим пользователя указать предпочитаемую версию движка
    clock_t start, end;
    float version_choice;
    char next_chr;
    unsigned short scanf_result;
    char buffer[256];
    choosing_version:
    //fgets(buffer, sizeof(buffer), stdin);
    printf("State preferable version of Godot Engine (example: 4.1): ");
    scanf_result = scanf("%f%c", &version_choice, &next_chr);
    //getchar();
    fgets(buffer, sizeof(buffer), stdin);
    endl;
    if (scanf_result == 0 || next_chr != '\n')
    {
        printf("State correct input format!\n");
        //printf("The version you stated is %f\nThe char that you stated is %c", version_choice, next_chr);
        goto choosing_version;
    }
    if (version_choice < 4.1f)
    {
        printf("State version which is equal or greater than 4.1!\n");
        goto choosing_version;
    }
    //Поскольку есть приколисты, округляем число до десятых
    floor_to(10, &version_choice);
    printf("Your project will have version of %.1f\nAre you sure? (y - yes, otherwise - no)\n", version_choice);
    decision = getchar();
    fgets(buffer, sizeof(buffer), stdin);
    endl;
    if (decision != 'y')
        goto choosing_version;
    //printf("The version was corrected to %.1f\n", version_choice);

    //Просим пользователя указать имя папки, которая создастся под проект
    char folder_name[256];
    giving_folder_name:
    //fgets(buffer, sizeof(buffer), stdin);
    printf("Give a name to a folder of the future GDExtension project: ");
    //Нулевой символ добавится в конце введённой строки автоматически
    //& не нужен, поскольку это по-умолчанию указатель
    scanf("%255[^\n]", folder_name);
    fgets(buffer, sizeof(buffer), stdin);
    //getchar();
    //fflush(stdin);
    endl;
    if (has_forbidden_symbols(folder_name))
    {
        printf("You stated forbidden symbols!\n");
        goto giving_folder_name;
    }
    printf("You stated '%s'. Are you sure you want to continue with it? (y - yes, otherwise - no)\n", folder_name);
    decision = getchar();
    fgets(buffer, sizeof(buffer), stdin);
    endl;
    if (decision != 'y')
        goto giving_folder_name;

    //Спрашиваем про директорию: использовать текущею, или поменять на другую
    printf("'%s' will be created in current directory. Is this okay? y - yes (The program will use current directory), anything else - go to stating directory: ", folder_name);
    decision = getchar();
    fgets(buffer, sizeof(buffer), stdin);
    endl;
    char current_working_directory[1024];
    if (decision == 'y')
    {
        //Здесь оно и помещает в переменную путь, и проверяет доступность этого пути
        if (getcwd(current_working_directory, sizeof(current_working_directory)) == NULL)
        {
            printf("An error occured in attempt to open current directory!\n");
            printf("Program finished!\n");
            system("pause");
            return -1;
        }
    }
    else
    {
        directory_state:
        printf("State an existing directory: ");
        scanf("%1023[^\n]", &current_working_directory);
        fgets(buffer, sizeof(buffer), stdin);
        //getchar();
        endl;
        if (!is_directory_exists(current_working_directory))
        {
            printf("The stated directory DOES NOT exist!\n");
            goto directory_state;
        }
        //fgets(buffer, sizeof(buffer), stdin);
        printf("You stated '%s'\nAre you sure you want to create your project there? (y - yes, otherwise - no): ", current_working_directory);
        decision = getchar();
        endl;
        if (decision != 'y')
            goto directory_state;
        //Переходим по указанному пути
        chdir(current_working_directory);
    }
    //Создаём названную папку в указанной директории
    mkdir(folder_name);
    //Сразу переходим в созданную папку
    chdir(folder_name);

    signed char cores_amount;
    getting_cores:
    //Просим указать количество ядер, которое будет использоваться для компиляции проекта
    printf("How many CPU cores will be used to compile the project?\nYou have %d available CPU cores\n(0 - use all cores except for 1. X<0 - use all cores except for 1-X (if result of the addition reaches maximum of the available CPU cores, it will use only 1 core)).\n", pthread_num_processors_np());
    scanf_result = scanf("%hhu%c", &cores_amount, &next_chr);
    fgets(buffer, sizeof(buffer), stdin);
    //getchar();
    //fflush(stdin);
    endl;
    if (scanf_result == 0 || next_chr != '\n')
    {
        printf("State NUMBER of cores that will be used.\n");
        goto getting_cores;
    }
    if (cores_amount == 0)
        cores_amount = (unsigned char)(pthread_num_processors_np()-1);
    //Если ввели слишком большое количество ядер, использоваться будут все
    else if (cores_amount > ((unsigned char)pthread_num_processors_np()))
        cores_amount = (unsigned char)pthread_num_processors_np();
    else if (cores_amount < 0)
        cores_amount = max(1, ((unsigned char)pthread_num_processors_np())+cores_amount-1);
    printf("Compilator will use %d out of %d available cores\nAre you sure? (y - yes, otherwise - no)\n", cores_amount, ((unsigned char)pthread_num_processors_np()));
    decision = getchar();
    fgets(buffer, sizeof(buffer), stdin);
    endl;
    if(decision != 'y')
        goto getting_cores;

    printf("Creating your project. Wait until it's done...\n\n");
    sleep(3);
    start = clock();
    char *command = malloc(sizeof(char) * 60);
    sprintf(command, "git clone -b %.1f https://github.com/godotengine/godot-cpp", version_choice);
    system(command);
    free(command);
    /*Функция system() блокирует выполнение программы до тех пор, пока внешняя команда (git clone) не завершится.
    Таким образом, ваша программа будет ожидать полного завершения клонирования репозитория перед продолжением своей работы.
    */
    
    //Переходим в папку репозитория и достаём подмодули
    chdir("godot-cpp");
    system("git submodule update --init");

    //Компилируем проект
    command = malloc(sizeof(char) * 37);
    sprintf(command, "scons -j%d target=template_debug", cores_amount);
    system(command);
    endl;
    sprintf(command, "scons -j%d target=template_release", cores_amount);
    system(command);
    endl;
    free(command);

    //Поднимаемся на папку выше, создаём и переходим в папку src
    chdir("..");
    mkdir("src");
    chdir("src");

    //Создаём файл register_types.h
    FILE *file = fopen("register_types.h", "w");
    if (file == NULL)
    {
        printf("An error occured in attempt to create register_types.h file!\n");
        printf("Program finished!\n");
        system("pause");
        return -1;
    }
    //Перенёс библиотеки в заголовочный файл, потому что так гораздо практичнее
    fprintf(file, "#ifndef REGISTER_TYPES_H\n#define REGISTER_TYPES_H\n\n#include <gdextension_interface.h>\n#include <godot_cpp/core/defs.hpp>\n#include <godot_cpp/core/class_db.hpp>\n#include <godot_cpp/godot.hpp>\n\nvoid initialize_module();\nvoid unitialize_module();\n\n#endif");
    fclose(file);

    //Создаём файл register_types.cpp
    file = fopen("register_types.cpp", "w");
    if (file == NULL)
    {
        printf("An error occured in attempt to create register_types.cpp file!\n");
        printf("Program finished!\n");
        system("pause");
        return -1;
    }
    //Файл создаётся, но программа вылетает по причине слишком большой длины строки в одинарных кавычках
    fprintf(file, "#include ");
    fwrap_in_double_quotes(file, "register_types.h");
    fprintf(file, "\n\nusing namespace godot;\n\n");
    fprintf(file, "void initialize_module(ModuleInitializationLevel p_level)\n{\n\tif (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)\n\t\treturn;\n}\n\n");
    fprintf(file, "void unitialize_module(ModuleInitializationLevel p_level)\n{\n\tif (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)\n\t\treturn;\n}\n\n");
    
    fprintf(file, "extern ");
    fwrap_in_double_quotes(file, "C");
    fprintf(file, "\n{\n\tGDExtensionBool GDE_EXPORT module_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)\n\t{\n\t\tgodot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);\n\n\t\tinit_obj.register_initializer(initialize_module);\n\t\tinit_obj.register_terminator(unitialize_module);\n\t\tinit_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);\n\n\t\treturn init_obj.init();\n\t}\n}");
    fclose(file);

    //Поднимаемся на директорию выше
    chdir("..");

    //Создаём файл SConstruct.py
    file = fopen("SConstruct.py", "w");
    if (file == NULL)
    {
        printf("An error occured in attempt to create SConstruct.py file!\n");
        printf("Program finished!\n");
        system("pause");
        return -1;
    }
    fprintf(file, "#!/usr/bin/env python\nimport os\nimport sys\n\nenv = SConscript(");
    fwrap_in_double_quotes(file, "godot-cpp/SConstruct");
    fprintf(file, ")\n\n");
    fprintf(file, "#For reference:\n#- CCFLAGS are compilation flags shared between C and C++\n#- CFLAGS are for C-specific compilation flags\n#- CXXFLAGS are for C++-specific compilation flags\n#- CPPFLAGS are for pre-processor flags\n#- CPPDEFINES are for pre-processor defines\n#- LINKFLAGS are for linking flags\n\n");
    
    fprintf(file, "#tweak this if you want to use different folders, or more folders, to store your source code in.\nenv.Append(CPPPATH=[");
    fwrap_in_double_quotes(file, "src/");
    fprintf(file, "])\nsources = Glob(");
    fwrap_in_double_quotes(file, "src/*.cpp");
    fprintf(file, ")\n\n");

    fprintf(file, "if env[");
    fwrap_in_double_quotes(file, "platform");
    fprintf(file, "] == ");
    fwrap_in_double_quotes(file, "macos");
    fprintf(file, ":\n\tlibrary = env.SharedLibrary(\n\t\t");
    fprint_double_quote(file);
    fprintf(file, "%s/bin/%s.{}.{}.framework/%s.{}.{}", folder_name, folder_name, folder_name);
    fwrap_in_double_quotes(file, ".format(\n\t\t\tenv[");
    fprintf(file, "platform");
    fwrap_in_double_quotes(file, "], env[");
    fprintf(file, "target");
    fwrap_in_double_quotes(file, "], env[");
    fprintf(file, "platform");
    fwrap_in_double_quotes(file, "], env[");
    fprintf(file, "target");
    fprint_double_quote(file);
    fprintf(file, "]\n\t\t),\n\t\tsource=sources,\n\t)\n");

    fprintf(file, "else:\n\tlibrary = env.SharedLibrary(\n\t\t");
    fprint_double_quote(file);
    fprintf(file, "%s/bin/%s{}{}", folder_name, folder_name);
    fprint_double_quote(file);
    fprintf(file, ".format(env[");
    fwrap_in_double_quotes(file, "suffix");
    fprintf(file, "], env[");
    fwrap_in_double_quotes(file, "SHLIBSUFFIX");
    fprintf(file, "]),\n\t\tsource=sources,\n\t)\n\nDefault(library)");
    fclose(file);

    //Компилируем проект ещё раз
    command = malloc(sizeof(char) * 37);
    sprintf(command, "scons -j%d target=template_debug", cores_amount);
    system(command);
    endl;
    sprintf(command, "scons -j%d target=template_release", cores_amount);
    system(command);
    endl;
    free(command);

    //Заходим в подпапку, которая имеет то же название, что и надпапка
    chdir(folder_name);
    chdir("bin");

    //Создаём файл .gdextension
    command = malloc(sizeof(char) * 271);
    sprintf(command, "%s.gdextension", folder_name);
    file = fopen(command, "w");
    if (file == NULL)
    {
        printf("An error occured in attempt to create %s file!\n", command);
        printf("Program finished!\n");
        system("pause");
        return -1;
    }
    free(command);

    fprintf(file, "[configuration]\n\nentry_symbol = ");
    fwrap_in_double_quotes(file, "module_init");
    fprintf(file, "\ncompatibility_minimum = %.1f\n\n[libraries]\n\n", version_choice);
    
    fprintf(file, "linux.x86_64.debug = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.linux.template_debug.x86_64.so", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");

    fprintf(file, "linux.x86_64.release = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.linux.template_release.x86_64.so", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");

    fprintf(file, "linux.debug.arm64 = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.linux.template_debug.arm64.so", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");

    fprintf(file, "linux.release.arm64 = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.linux.template_release.arm64.so", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");
    
    fprintf(file, "windows.x86_64.debug = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.windows.template_debug.x86_64.dll", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");

    fprintf(file, "windows.x86_64.release = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.windows.template_release.x86_64.dll", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");

    fprintf(file, "macos.debug = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.macos.template_debug.framework", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");

    fprintf(file, "macos.release = ");
    fprint_double_quote(file);
    fprintf(file, "res://bin/%s.macos.template_release.framework", folder_name);
    fprint_double_quote(file);
    fprintf(file, "\n");
    fclose(file);
    end = clock();

    double time_result = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Everything is done in %f seconds (%f minutes)!\n", time_result, time_result/60);
    endl;
    printf("Program finished!\n");
    system("pause");
    return 0;
}