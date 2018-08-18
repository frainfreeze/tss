#ifndef BUILTINS_H__
#define BUILTINS_H__

#include <iostream>
#include <string>
#include <functional>
#include <map>

#include <unistd.h> //chdir

/**
 * builtin shell commands
 */
namespace builtins {
/**
 * @brief internal helper function
 * @return List of builting functions
 */
std::string tss_get();

/**
 * @brief Builtin command: change directory.
 * @param dir: directory to cd to.
 * @return Always returns 1, to continue executing.
 */
int tss_cd(std::string dir)
{
    int chdir_return_value = chdir(dir.c_str());
    return 1; // todo: catch errors
}

/**
 * @brief Builtin command: print help.
 * @return Always returns 1 to continue execution.
 */
int tss_help(std::string name)
{
    std::cout << "Tom's simple shell\n"
              << "These shell commands are defined internally. Type 'help' to see this list.\n"
              << "Type 'help name' to find out more about the function 'name'.\n"
              << "The following are built in: "
              << tss_get()
              << std::endl;
    /// \todo Help for individual commands
    return 1;
}

/**
 * @brief builtin shell commands functions map
 */
std::map<std::string, std::function<int(std::string)>>  funcMap =
         {{ "cd", tss_cd},
          { "help", tss_help}
         };

std::string tss_get()
{
    std::string str;
    for(auto elem : funcMap)
        str.append("\n " + elem.first);
    return str;
}

}
#endif // BUILTINS_H__