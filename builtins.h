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
 */
void tss_help()
{
    std::cout << "Tom's simple shell\n"
              << "These shell commands are defined internally. Type 'help' to see this list.\n"
              << "Type 'help name' to find out more about the function 'name'.\n"
              << "Use 'info bash' to find out more about the shell in general.\n"
              << "The following are built in:"
              << std::endl;
    /// \todo List builtins
}

}
#endif // BUILTINS_H__